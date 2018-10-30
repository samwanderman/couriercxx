/*
 * I2CPortBase.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "I2CPortBase.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

I2CPortBase::I2CPortBase(std::string path, uint8_t addr) : IConnectorBase() {
	this->name = name;
	this->addr = addr;
}

I2CPortBase::~I2CPortBase() { }

int I2CPortBase::open() {
	if (IConnectorBase::open() == -1) {
		return -1;
	}

	fd = ::open(name.c_str(), O_RDWR);
	if (fd == -1) {
		return -1;
	}

	if (ioctl(fd, I2C_SLAVE, addr) < 0) {
		close();

		return -1;
	}

	return 0;
}

int I2CPortBase::close() {
	if (IConnectorBase::close() == -1) {
		return -1;
	}

	return ::close(fd);
}

int I2CPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::read(fd, buffer, bufferSize);
}

int I2CPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::write(fd, buffer, bufferSize);
}
