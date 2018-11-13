/*
 * Info.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Info.h"

namespace Connection {

Info::Info(int32_t id, std::string name, uint64_t commandTimeout) {
	this->id = id;
	this->name = name;
	this->commandTimeout = commandTimeout;
}

Info::Info(int32_t id) : Info(id, "", 0) { }

Info::~Info() { }

int32_t Info::getId() const {
	return id;
}

std::string Info::getName() const {
	return name;
}

uint64_t Info::getCommandTimeout() const {
	return commandTimeout;
}

}
