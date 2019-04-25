/*
 * SCSIPortBase.cpp
 *
 *  Created on: 25.04.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SCSIPortBase.h"

#include <fcntl.h>
#include <unistd.h>

SCSIPortBase::SCSIPortBase(std::string port) {
	this->port = port;
}

SCSIPortBase::~SCSIPortBase() { }

int SCSIPortBase::open() {
	fd = ::open(this->port.c_str(), O_RDWR);

	return fd;
}

int SCSIPortBase::close() {
	return ::close(fd);
}

int SCSIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}

int SCSIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}
