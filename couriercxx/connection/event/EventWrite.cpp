/*
 * EventWrite.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventWrite.h"

#include <cstring>

#include "../Connection.h"

class ConnectionInfo;

namespace Connection {

EventWrite::EventWrite(const Info* info, const uint8_t* data, uint32_t dataLen) : IEvent(Connection::EVENT_WRITE), EventConnection(info) {
	if ((data != nullptr) && (dataLen > 0)) {
		this->data = new uint8_t[dataLen];
		this->dataLen = dataLen;
		memmove(this->data, data, sizeof(uint8_t) * this->dataLen);
	} else {
		this->data = nullptr;
		this->dataLen = 0;
	}
}

EventWrite::EventWrite(const Info* info, const uint8_t* data, uint32_t dataLen, IListener* source, IListener* target) : IEvent(Connection::EVENT_WRITE, source, target), EventConnection(info) {
	if ((data != nullptr) && (dataLen > 0)) {
		this->data = new uint8_t[dataLen];
		this->dataLen = dataLen;
		memmove(this->data, data, sizeof(uint8_t) * this->dataLen);
	} else {
		this->data = nullptr;
		this->dataLen = 0;
	}
}

EventWrite::EventWrite(const EventWrite& other) : IEvent(other), EventConnection(other) {
	if (other.dataLen > 0) {
		dataLen = other.dataLen;
		data = new uint8_t[dataLen];
		memmove(data, other.data, dataLen * sizeof(uint8_t));
	} else {
		data = nullptr;
	}
}

EventWrite::EventWrite(EventWrite&& other) : IEvent(other), EventConnection(other) {
	dataLen = other.dataLen;
	data = other.data;
	other.data = nullptr;
}

EventWrite::~EventWrite() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

EventWrite& EventWrite::operator=(const EventWrite& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);

	if (this != &other) {
		if (other.dataLen > 0) {
			dataLen = other.dataLen;
			data = new uint8_t[dataLen];
			memmove(data, other.data, dataLen * sizeof(uint8_t));
		} else {
			data = nullptr;
			dataLen = 0;
		}
	}

	return *this;
}

EventWrite& EventWrite::operator=(EventWrite&& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);

	if (this != &other) {
		dataLen = other.dataLen;
		data = other.data;
		other.data = nullptr;
	}

	return *this;
}

uint32_t EventWrite::getDataLen() {
	return dataLen;
}

int EventWrite::getData(uint8_t* data, uint32_t dataLen) {
	if ((this->data == nullptr) || (data == nullptr) || (dataLen == 0) || (this->dataLen == 0)) {
		return -1;
	}

	uint32_t minLen = dataLen > this->dataLen ? this->dataLen : dataLen;
	memmove(data, this->data, sizeof(uint8_t) * minLen);

	return 0;
}

uint8_t* EventWrite::getData() {
	return this->data;
}

} /* namespace Connection */
