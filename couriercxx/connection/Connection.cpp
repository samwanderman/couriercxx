/*
 * Connection.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Connection.h"

#include <unistd.h>
#include <cstdint>
#include <thread>

#include "../connector/IConnectorBase.h"
#include "../event/Dispatcher.h"
#include "../logger/Log.h"
#include "event/EventRead.h"
#include "Info.h"

#define BUFFER_MAX_SIZE	1024
#define MAX_EVENTS		128

namespace Connection {

const EVENT_T Connection::EVENT_READ	= IEvent::genEventId();
const EVENT_T Connection::EVENT_WRITE	= IEvent::genEventId();
const EVENT_T Connection::EVENT_STATUS	= IEvent::genEventId();

Connection::Connection(const Info* info, IConnectorBase* connector) {
	this->info = info;
	this->connector = connector;
	readThreadRunning = false;
	eventsThreadRunning = false;
}

Connection::~Connection() {
	readThreadRunning = false;

	if (connector != nullptr) {
		delete connector;
		connector = nullptr;
	}

	if (info != nullptr) {
		delete info;
		info = nullptr;
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

	readThreadRunning = true;

	auto readThreadFunc = [this]() {
		while (this->readThreadRunning) {
			uint8_t buffer[BUFFER_MAX_SIZE];
			int bytesRead = this->connector->read(buffer, BUFFER_MAX_SIZE);
			if (bytesRead == -1) {
				Log::error("Connection.read() error");
			} else if (bytesRead > 0) {
				Log::debug("Connection.read() %i bytes", bytesRead);
				EventRead* event = new EventRead(this->info, buffer, bytesRead);
				Dispatcher::trigger(event);
			}

			usleep(100000);
		}
	};
	std::thread readThread(readThreadFunc);
	readThread.detach();

	eventsThreadRunning = true;

	auto eventsThreadFunc = [this]() {
		while (eventsThreadRunning) {
			eventsListMutex.lock();
			if (eventsList.size() > 0) {
				EventWrite* ev = eventsList.front();
				int res = this->connector->write(ev->getData(), ev->getDataLen());
				Log::debug("Connection.write() %i bytes", res);
				eventsList.pop_front();
				delete ev;
				usleep(info->getCommandTimeout() * 1000);
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

	readThreadRunning = false;

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
