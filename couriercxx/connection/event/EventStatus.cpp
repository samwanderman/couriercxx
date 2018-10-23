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

} /* namespace Connection */
