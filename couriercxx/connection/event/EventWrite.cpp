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

namespace Connection {

EventWrite::EventWrite(const Info info, const uint8_t* data, uint32_t dataSize) : IEvent(Connection::EVENT_WRITE), EventConnection(info) {
	if ((data != nullptr) && (dataSize > 0)) {
		this->data = new uint8_t[dataSize];
		this->dataSize = dataSize;
		memmove(this->data, data, sizeof(uint8_t) * this->dataSize);
	} else {
		this->data = nullptr;
		this->dataSize = 0;
	}
}

EventWrite::EventWrite(const Info info, const uint8_t* data, uint32_t dataSize, IListener* source, IListener* target) : IEvent(Connection::EVENT_WRITE, source, target), EventConnection(info) {
	if ((data != nullptr) && (dataSize > 0)) {
		this->data = new uint8_t[dataSize];
		this->dataSize = dataSize;
		memmove(this->data, data, sizeof(uint8_t) * this->dataSize);
	} else {
		this->data = nullptr;
		this->dataSize = 0;
	}
}

EventWrite::EventWrite(const EventWrite& other) : IEvent(other), EventConnection(other) {
	if (other.dataSize > 0) {
		dataSize = other.dataSize;
		data = new uint8_t[dataSize];
		memmove(data, other.data, dataSize * sizeof(uint8_t));
	} else {
		data = nullptr;
	}
}

EventWrite::EventWrite(EventWrite&& other) : IEvent(other), EventConnection(other) {
	dataSize = other.dataSize;
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
		if (other.dataSize > 0) {
			dataSize = other.dataSize;
			data = new uint8_t[dataSize];
			memmove(data, other.data, dataSize * sizeof(uint8_t));
		} else {
			data = nullptr;
			dataSize = 0;
		}
	}

	return *this;
}

EventWrite& EventWrite::operator=(EventWrite&& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);

	if (this != &other) {
		dataSize = other.dataSize;
		data = other.data;
		other.data = nullptr;
	}

	return *this;
}

uint32_t EventWrite::getDataSize() const {
	return dataSize;
}

int EventWrite::getData(uint8_t* data, uint32_t dataSize) const {
	if ((this->data == nullptr) || (data == nullptr) || (dataSize == 0) || (this->dataSize == 0)) {
		return -1;
	}

	uint32_t minLen = dataSize > this->dataSize ? this->dataSize : dataSize;
	memmove(data, this->data, sizeof(uint8_t) * minLen);

	return 0;
}

const uint8_t* EventWrite::getData() const {
	return this->data;
}

} /* namespace Connection */
