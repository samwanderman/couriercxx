/*
 * EventStatus.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventStatus.h"

#include "../Connection.h"

namespace Connection {

EventStatus::EventStatus(const Info* info, uint8_t status) : IEvent(Connection::EVENT_STATUS), EventConnection(info) {
	this->status = status;
}

EventStatus::EventStatus(const Info* info, uint8_t status, IListener* source, IListener* target) : IEvent(Connection::EVENT_STATUS, source, target), EventConnection(info) {
	this->status = status;
}

EventStatus::~EventStatus() { }

EventStatus::EventStatus(const EventStatus& other) : IEvent(other), EventConnection(other) {
	status = other.status;
}

EventStatus::EventStatus(EventStatus&& other) : IEvent(other), EventConnection(other) {
	status = other.status;
}

EventStatus& EventStatus::operator=(const EventStatus& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);
	status = other.status;

	return *this;
}

EventStatus& EventStatus::operator=(EventStatus&& other) {
	IEvent::operator=(other);
	EventConnection::operator=(other);
	status = other.status;

	return *this;
}


} /* namespace Connection */
