/*
 * EventConnection.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "EventConnection.h"

#include <cstdlib>
#include <cstring>

#include "../Info.h"

namespace Connection {

EventConnection::EventConnection(const Info* info) {
	this->info = (Info*) malloc(sizeof(Info));
	memmove((void*) this->info, info, sizeof(Info));
}

EventConnection::~EventConnection() {
	if (info != nullptr) {
		free((void*) info);
	}
}

EventConnection::EventConnection(const EventConnection& other) {
	info = (Info*) malloc(sizeof(Info));
	memmove((void*) info, other.info, sizeof(Info));
}

EventConnection::EventConnection(EventConnection&& other) {
	info = other.info;
	other.info = nullptr;
}

EventConnection& EventConnection::operator=(const EventConnection& other) {
	this->info = (Info*) malloc(sizeof(Info));
	memmove((void*) this->info, info, sizeof(Info));

	return *this;
}

EventConnection& EventConnection::operator=(EventConnection&& other) {
	info = other.info;
	other.info = nullptr;

	return *this;
}

const Info* EventConnection::getInfo() const {
	Info* info = (Info*) malloc(sizeof(Info));
	memmove(info, this->info, sizeof(Info));

	return info;
}

}
