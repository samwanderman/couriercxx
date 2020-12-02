/*
 * Connection.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Connection.h"

#include <cstdint>
#include <cstdio>
#include <thread>

#include "../connector/IConnectorBase.h"
#include "../event/Dispatcher.h"
#include "../logger/Log.h"
#include "../util/System.h"
#include "event/EventRead.h"

#define BUFFER_MAX_SIZE			1024
#define MAX_EVENTS				128

namespace Connection {

const EVENT_T Connection::EVENT_READ	= IEvent::genEventId();
const EVENT_T Connection::EVENT_WRITE	= IEvent::genEventId();
const EVENT_T Connection::EVENT_STATUS	= IEvent::genEventId();

Connection::Connection(const Info info, IConnectorBase* connector) {
	this->info		= info;
	this->connector = connector;
}

Connection::~Connection() {
	if (connector != nullptr) {
		delete connector;
		connector = nullptr;
	}
}

int Connection::enable() {
	Log::debug("Connection[%i].enable()", info.id);

	if (isEnabled()) {
		return -1;
	}

	Dispatcher::addListener(Connection::EVENT_WRITE, this);

	running.store(true);

	connect();

	return IListener::enable();
}

int Connection::disable() {
	Log::debug("Connection[%i].disable()", info.id);

	if (!isEnabled()) {
		return -1;
	}

	Dispatcher::removeListener(Connection::EVENT_WRITE, this);

	running.store(false);
	cond.notify_all();

	IListener::disable();

	return disconnect();
}

void Connection::on(const IEvent* event) {
	if (event->getType() == Connection::EVENT_WRITE) {
		Log::debug("Connection[%i].on(EVENT_WRITE)", info.id);
		std::unique_lock lock(eventsListMutex);
		if (eventsList.size() >= MAX_EVENTS) {
			eventsList.pop_front();
		}
		eventsList.push_back(new EventWrite(*dynamic_cast<const EventWrite*>(event)));
		cond.notify_all();
	} else if (event->getType() == Connection::EVENT_STATUS) {
		Log::debug("Connection[%i].on(EVENT_STATUS)", info.id);
	}
}

int Connection::connect() {
	stopThreads.store(false);

	lazyStart = std::thread([this]() {
		int res = -1;
		// try to connect or die
		while ((res = connector->open()) == -1) {
			// if threads stopped
			if (stopThreads.load()) {
				return;
			}

			// if no reconnect on errors
			if (!info.reconnectOnErrors) {
				return;
			}

			// wait for timeout
			System::sleep(info.reconnectTimeout);
		}

		readThread = std::thread([this]() {
			while (!stopThreads.load()) {
				uint8_t buffer[BUFFER_MAX_SIZE];
				int bytesRead = this->connector->read(buffer, BUFFER_MAX_SIZE, 200);
				if (bytesRead == -1) {
					return reconnect();
				} else if (bytesRead > 0) {
					Dispatcher::trigger(new EventRead(this->info, buffer, bytesRead));
				}
			}
		});

		eventsThread = std::thread([this]() {
			while (!stopThreads.load()) {
				std::unique_lock<decltype(eventsListMutex)> lock(eventsListMutex);
				cond.wait(lock);
				while (eventsList.size() > 0) {
					EventWrite* ev = eventsList.front();
					int res = this->connector->write(ev->getData(), ev->getDataSize());
					eventsList.pop_front();
					delete ev;

					if (res == -1) {
						return reconnect();
					}
				}

				System::sleep(info.commandTimeout);
			}
		});
	});

	return 0;
}

int Connection::disconnect() {
	stopThreads.store(true);

	if (eventsThread.joinable()) {
		eventsThread.join();
	}

	if (readThread.joinable()) {
		readThread.join();
	}

	if (lazyStart.joinable()) {
		lazyStart.join();
	}

	return connector->close();
}

int Connection::reconnect() {
	disconnect();

	if (running.load()) {
		connect();
	}

	return 0;
}

Info Connection::getInfo() {
	return info;
}

}
