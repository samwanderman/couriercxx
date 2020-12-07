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
#define CONNECTION_READ_TIMEOUT	100

namespace Connection {

const EVENT_T EVENT_READ	= IEvent::genEventId();
const EVENT_T EVENT_WRITE	= IEvent::genEventId();
const EVENT_T EVENT_STATUS	= IEvent::genEventId();

//const EVENT_T Connection::EVENT_READ	= IEvent::genEventId();
//const EVENT_T Connection::EVENT_WRITE	= IEvent::genEventId();
//const EVENT_T Connection::EVENT_STATUS	= IEvent::genEventId();

Connection::Connection(const Info info, IConnectorBase* connector) {
	this->info = info;
	this->connector = connector;
	running = false;
}

Connection::~Connection() {
	running = false;

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

	int res = connector->open();
	if (res == -1) {
		return -1;
	}

	Dispatcher::addListener(EVENT_WRITE, this);

	running = true;

	auto readThreadFunc = [this]() {
		while (running) {
			uint8_t buffer[BUFFER_MAX_SIZE];
			int bytesRead = this->connector->read(buffer, BUFFER_MAX_SIZE, 200);
			if (bytesRead == -1) {
				Log::error("Connection[%i].read() error %i", info.id, bytesRead);
				perror("");
			} else if (bytesRead > 0) {
				Log::debug("Connection[%i].read() %i bytes", info.id, bytesRead);
#ifdef DEBUG
				Log::log("<< ");
				for (int i = 0; i < bytesRead; i++) {
					Log::log("%x ", buffer[i]);
				}
				Log::log("\r\n");
#endif
				Dispatcher::trigger(new EventRead(this->info, buffer, bytesRead));
			}

			System::sleep(CONNECTION_READ_TIMEOUT);
		}
	};
	readThread = std::thread(readThreadFunc);

	auto eventsThreadFunc = [this]() {
		while (running) {
			std::unique_lock<decltype(eventsListMutex)> lock(eventsListMutex);
			cond.wait(lock);
			while (eventsList.size() > 0) {
				EventWrite* ev = eventsList.front();
				int res = this->connector->write(ev->getData(), ev->getDataSize());
				Log::debug("Connection[%i].write() %i bytes", info.id, res);
#ifdef DEBUG
				Log::log(">> ");
				for (uint32_t i = 0; i < ev->getDataSize(); i++) {
					Log::log("%x ", ev->getData()[i]);
				}
				Log::log("\r\n");
#endif
				eventsList.pop_front();
				delete ev;
			}
			System::sleep(info.commandTimeout);
		}
	};
	eventsThread = std::thread(eventsThreadFunc);

	return IListener::enable();
}

int Connection::disable() {
	Log::debug("Connection[%i].disable()", info.id);

	if (!isEnabled()) {
		return -1;
	}

	Dispatcher::removeListener(EVENT_WRITE, this);

	running = false;
	cond.notify_all();

	if (eventsThread.joinable()) {
		eventsThread.join();
	}

	if (readThread.joinable()) {
		readThread.join();
	}

	int res = connector->close();
	IListener::disable();

	return res;
}

void Connection::on(const IEvent* event) {
	if (event->getType() == EVENT_WRITE) {
		Log::debug("Connection[%i].on(EVENT_WRITE)", info.id);
		std::unique_lock<decltype(eventsListMutex)> lock(eventsListMutex);
		if (eventsList.size() >= MAX_EVENTS) {
			eventsList.pop_front();
		}
		eventsList.push_back(new EventWrite(*dynamic_cast<const EventWrite*>(event)));
		cond.notify_all();
	} else if (event->getType() == EVENT_STATUS) {
		Log::debug("Connection[%i].on(EVENT_STATUS)", info.id);
	}
}

Info Connection::getInfo() {
	return info;
}

}
