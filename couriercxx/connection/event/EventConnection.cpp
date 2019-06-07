/*
 * EventConnection.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventConnection.h"

namespace Connection {

EventConnection::EventConnection(const Info info) {
	this->info = info;
}

EventConnection::~EventConnection() { }

const Info EventConnection::getInfo() const {
	return info;
}

}
