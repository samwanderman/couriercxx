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

class ConnectionInfo;

namespace Connection {

EventRead::EventRead(const Info* info, const uint8_t* data, uint32_t dataLen) : IEvent(Connection::EVENT_READ), EventConnection(info) {
	if ((data != nullptr) && (dataLen > 0)) {
		this->data = new uint8_t[dataLen];
		this->dataLen = dataLen;
		memmove(this->data, data, sizeof(uint8_t) * this->dataLen);
	} else {
		this->data = nullptr;
		this->dataLen = 0;
	}
}

EventRead::EventRead(const Info* info, const uint8_t* data, uint32_t dataLen, IListener* source, IListener* target) : IEvent(Connection::EVENT_READ, source, target), EventConnection(info) {
	if ((data != nullptr) && (dataLen > 0)) {
		this->data = new uint8_t[dataLen];
		this->dataLen = dataLen;
		memmove(this->data, data, sizeof(uint8_t) * this->dataLen);
	} else {
		this->data = nullptr;
		this->dataLen = 0;
	}
}

EventRead::EventRead(const EventRead& other) : IEvent(other), EventConnection(other) {
	dataLen = other.dataLen;
	if (dataLen > 0) {
		data = new uint8_t[dataLen];
		memmove(data, &other, sizeof(uint8_t) * dataLen);
	} else {
		data = nullptr;
	}
}

EventRead::EventRead(EventRead&& other) : IEvent(other), EventConnection(other) {
	dataLen = other.dataLen;
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
		dataLen = other.dataLen;
		if (dataLen > 0) {
			data = new uint8_t[dataLen];
			memmove(data, &other, sizeof(uint8_t) * dataLen);
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
		dataLen = other.dataLen;
		data = other.data;
		other.data = nullptr;
	}

	return *this;
}

uint32_t EventRead::getDataLen() const {
	return dataLen;
}

int EventRead::getData(uint8_t* buffer, uint32_t bufferSize) const {
	if ((data == nullptr) || (buffer == nullptr) || (bufferSize == 0) || (dataLen == 0)) {
		return -1;
	}

	uint32_t minLen = bufferSize > dataLen ? dataLen : bufferSize;
	memmove(buffer, data, sizeof(uint8_t) * minLen);

	return 0;
}

uint8_t* EventRead::getData() const {
	return this->data;
}

} /* namespace Connection */
