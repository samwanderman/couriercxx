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
#include "event/EventWrite.h"
#include "Info.h"

#define BUFFER_MAX_SIZE	1024

namespace Connection {

const EVENT_T Connection::EVENT_READ = IEvent::genEventId();
const EVENT_T Connection::EVENT_WRITE = IEvent::genEventId();
const EVENT_T Connection::EVENT_STATUS = IEvent::genEventId();

Connection::Connection(const Info* info, IConnectorBase* connector) {
	this->info = info;
	this->connector = connector;
	readThreadRunning = false;
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
	int res = connector->open();

	if (res == -1) {
		return -1;
	}

	Dispatcher::addListener(Connection::EVENT_WRITE, this);

	readThreadRunning = true;

	auto func = [this]() {
		while (this->readThreadRunning) {
			uint8_t buffer[BUFFER_MAX_SIZE];
			int bytesRead = this->connector->read(buffer, BUFFER_MAX_SIZE);
			if (bytesRead == -1) {
				Log::error("Adapter.read() error");
			} else if (bytesRead > 0) {
				Log::debug("Adapter.read() %i bytes", bytesRead);
				EventRead* event = new EventRead(this->info, buffer, bytesRead);
				Dispatcher::trigger(event);
			}

			usleep(100000);
		}
	};

	std::thread thread(func);
	thread.detach();

	return res;
}

int Connection::disable() {
	readThreadRunning = false;

	Dispatcher::removeListener(Connection::EVENT_WRITE, this);

	return connector->close();
}

void Connection::on(IEvent* event) {
	if (event->getType() == Connection::EVENT_WRITE) {
		Log::debug("Connection.on(EVENT_WRITE)");
		EventWrite* writeEvent = dynamic_cast<EventWrite*>(event);
		int res = this->connector->write(writeEvent->getData(), writeEvent->getDataLen());
		Log::debug("Adapter.write() %i bytes", res);
	} else if (event->getType() == Connection::EVENT_STATUS) {
		Log::debug("Connection.on(EVENT_STATUS)");
	}
}

}
