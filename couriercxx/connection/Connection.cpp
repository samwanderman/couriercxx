/*
 * Connection.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Connection.h"

#include <cstdint>
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

const EVENT_T Connection::EVENT_READ	= IEvent::genEventId();
const EVENT_T Connection::EVENT_WRITE	= IEvent::genEventId();
const EVENT_T Connection::EVENT_STATUS	= IEvent::genEventId();

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
	if (isEnabled()) {
		return -1;
	}

	Log::debug("Connection.enable()");

	int res = connector->open();
	if (res == -1) {
		return -1;
	}

	Dispatcher::addListener(Connection::EVENT_WRITE, this);

	running = true;

	auto readThreadFunc = [this]() {
		while (running) {
			uint8_t buffer[BUFFER_MAX_SIZE];
			int bytesRead = this->connector->read(buffer, BUFFER_MAX_SIZE);
			if (bytesRead == -1) {
				Log::error("Connection.read() error");
			} else if (bytesRead > 0) {
				Log::debug("Connection.read() %i bytes", bytesRead);
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
	std::thread readThread(readThreadFunc);
	readThread.detach();

	auto eventsThreadFunc = [this]() {
		while (running) {
			eventsListMutex.lock();
			if (eventsList.size() > 0) {
				EventWrite* ev = eventsList.front();
				int res = this->connector->write(ev->getData(), ev->getDataLen());
				Log::debug("Connection.write() %i bytes", res);
#ifdef DEBUG
				Log::log(">> ");
				for (uint32_t i = 0; i < ev->getDataLen(); i++) {
					Log::log("%x ", ev->getData()[i]);
				}
				Log::log("\r\n");
#endif
				eventsList.pop_front();
				delete ev;
				System::sleep(info.commandTimeout);
			}
			eventsListMutex.unlock();
		}
	};
	std::thread thEvents(eventsThreadFunc);
	thEvents.detach();

	return IListener::enable();
}

int Connection::disable() {
	if (!isEnabled()) {
		return -1;
	}

	Log::debug("Connection.disable()");

	running = false;

	Dispatcher::removeListener(Connection::EVENT_WRITE, this);
	int res = connector->close();
	IListener::disable();

	return res;
}

void Connection::on(const IEvent* event) {
	if (event->getType() == Connection::EVENT_WRITE) {
		Log::debug("Connection.on(EVENT_WRITE)");
		eventsListMutex.lock();
		if (eventsList.size() >= MAX_EVENTS) {
			eventsList.pop_front();
		}
		eventsList.push_back(new EventWrite(*dynamic_cast<const EventWrite*>(event)));
		eventsListMutex.unlock();
		Log::debug("added event to queue");
	} else if (event->getType() == Connection::EVENT_STATUS) {
		Log::debug("Connection.on(EVENT_STATUS)");
	}
}

}
