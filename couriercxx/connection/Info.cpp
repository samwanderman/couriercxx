/*
 * Info.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Info.h"

namespace Connection {

Info::Info(int32_t id, std::string name) {
	this->id = id;
	this->name = name;
}

Info::~Info() { }

int32_t Info::getId() {
	return id;
}

std::string Info::getName() {
	return name;
}

}
