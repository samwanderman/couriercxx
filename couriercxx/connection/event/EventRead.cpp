/*
 * EventRead.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventRead.h"

#include <cstring>

#include "../Connection.h"

namespace Connection {

EventRead::EventRead(const Info info, const uint8_t* data, uint32_t dataSize) : IEvent(Connection::EVENT_READ), EventConnection(info) {
	if ((data != nullptr) && (dataSize > 0)) {
		this->data = new uint8_t[dataSize];
		this->dataSize = dataSize;
		memmove(this->data, data, sizeof(uint8_t) * this->dataSize);
	} else {
		this->data = nullptr;
		this->dataSize = 0;
	}
}

EventRead::EventRead(const Info info, const uint8_t* data, uint32_t dataSize, IListener* source, IListener* target) : IEvent(Connection::EVENT_READ, source, target), EventConnection(info) {
	if ((data != nullptr) && (dataSize > 0)) {
		this->data = new uint8_t[dataSize];
		this->dataSize = dataSize;
		memmove(this->data, data, sizeof(uint8_t) * this->dataSize);
	} else {
		this->data = nullptr;
		this->dataSize = 0;
	}
}

EventRead::EventRead(const EventRead& other) : IEvent(other), EventConnection(other) {
	dataSize = other.dataSize;
	if (dataSize > 0) {
		data = new uint8_t[dataSize];
		memmove(data, &other.data, sizeof(uint8_t) * dataSize);
	} else {
		data = nullptr;
	}
}

EventRead::EventRead(EventRead&& other) : IEvent(other), EventConnection(other) {
	dataSize = other.dataSize;
	data = other.data;
	other.data = nullptr;
}

EventRead::~EventRead() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

EventRead& EventRead::operator=(const EventRead& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);

	if (this != &other) {
		dataSize = other.dataSize;
		if (dataSize > 0) {
			data = new uint8_t[dataSize];
			memmove(data, &other.data, sizeof(uint8_t) * dataSize);
		} else {
			data = nullptr;
		}
	}

	return *this;
}

EventRead& EventRead::operator=(EventRead&& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);

	if (this != &other) {
		dataSize = other.dataSize;
		data = other.data;
		other.data = nullptr;
	}

	return *this;
}

uint32_t EventRead::getDataSize() const {
	return dataSize;
}

int EventRead::getData(uint8_t* buffer, uint32_t bufferSize) const {
	if ((data == nullptr) || (buffer == nullptr) || (bufferSize == 0) || (dataSize == 0)) {
		return -1;
	}

	uint32_t minLen = bufferSize > dataSize ? dataSize : bufferSize;
	memmove(buffer, data, sizeof(uint8_t) * minLen);

	return 0;
}

const uint8_t* EventRead::getData() const {
	return this->data;
}

} /* namespace Connection */
