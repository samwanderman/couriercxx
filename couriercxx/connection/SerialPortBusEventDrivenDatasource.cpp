/*
 * SerialPortBusEventDrivenDatasource.cpp
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBusEventDrivenDatasource.h"

#include <algorithm>
#include <cstring>

#include "../event/Dispatcher.h"
#include "Connection.h"
#include "event/EventRead.h"
#include "event/EventWrite.h"
#include "Info.h"

#define BUFFER_SIZE	4096

SerialPortBusEventDrivenDatasource::SerialPortBusEventDrivenDatasource(uint32_t connectionId) : IDatasource(), IListener() {
	this->connectionId = connectionId;
}

SerialPortBusEventDrivenDatasource::~SerialPortBusEventDrivenDatasource() { }

int SerialPortBusEventDrivenDatasource::enable() {
	tmpBuffer = new uint8_t[BUFFER_SIZE];
	tmpBufferSize = 0;

	Dispatcher::addListener(Connection::EVENT_READ, this);
	Dispatcher::addListener(Connection::EVENT_STATUS, this);

	return IListener::enable();
}

int SerialPortBusEventDrivenDatasource::disable() {
	int res = IListener::disable();

	Dispatcher::removeListener(Connection::EVENT_STATUS, this);
	Dispatcher::removeListener(Connection::EVENT_READ, this);

	if (tmpBuffer != nullptr) {
		delete[] tmpBuffer;
		tmpBuffer = nullptr;
		tmpBufferSize = 0;
	}

	return res;
}

int SerialPortBusEventDrivenDatasource::read(uint8_t* buffer, uint32_t bufferSize) {
	while (true) {
		accessMutex.lock();

		if (tmpBufferSize > 0) {
			uint32_t min = std::min(bufferSize, tmpBufferSize);
			memmove(buffer, tmpBuffer, min);
			memmove(tmpBuffer, &tmpBuffer[min], tmpBufferSize - min);
			tmpBufferSize -= min;
			accessMutex.unlock();

			return min;
		}

		accessMutex.unlock();
	}

	return 0;
}

int SerialPortBusEventDrivenDatasource::write(const uint8_t* buffer, uint32_t bufferSize) {
	Dispatcher::trigger(new Connection::EventWrite(Connection::Info(connectionId), buffer, bufferSize));

	return bufferSize;
}

void SerialPortBusEventDrivenDatasource::on(const IEvent* event) {
	if (event->getType() == Connection::EVENT_READ) {
		const Connection::EventRead* ev = dynamic_cast<const Connection::EventRead*>(event);

		accessMutex.lock();

		if (tmpBufferSize + ev->getDataSize() > BUFFER_SIZE) {
			uint32_t offset = tmpBufferSize + ev->getDataSize() - BUFFER_SIZE;
			memmove(tmpBuffer, &tmpBuffer[offset], tmpBufferSize - offset);
			tmpBufferSize -= offset;
		}

		memmove(&tmpBuffer[tmpBufferSize], ev->getData(), ev->getDataSize());
		tmpBufferSize += ev->getDataSize();

		accessMutex.unlock();
	}
}
