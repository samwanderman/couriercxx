/*
 * GPIOPortBase.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "GPIOPortBase.h"

#include <cstdio>
#include <cstring>

#include "../../util/IO.h"

#define EXPORT_PATH		"/sys/class/gpio/export"
#define UNEXPORT_PATH	"/sys/class/gpio/unexport"
#define DIRECTION_PATH	"/sys/class/gpio/gpio%i/direction"
#define VALUE_PATH		"/sys/class/gpio/gpio%i/value"

#define PATH_MAX_LEN	1024
#define VALUE_MAX_LEN	8

GPIOPortBase::GPIOPortBase(uint8_t pid) : IConnectorBase() {
	this->pid = pid;
}

GPIOPortBase::GPIOPortBase(uint8_t pid, Direction direction) : GPIOPortBase(pid) {
	this->direction = direction;
}

GPIOPortBase::~GPIOPortBase() { }

int GPIOPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	if (IO::exists(EXPORT_PATH)) {
		unexportGPIO();
	}

	int res = exportGPIO();
	if (res == -1) {
		return -1;
	}

	if (direction != NONE) {
		res = setDirection(direction);
	}

	if (res == -1) {
		clean();

		return -1;
	}

	return IConnectorBase::open();
}

int GPIOPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	clean();

	return IConnectorBase::close();
}

void GPIOPortBase::clean() {
	unexportGPIO();
}

int GPIOPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	if (direction == IN) {
		char path[PATH_MAX_LEN];
		memset(path, 0, PATH_MAX_LEN * sizeof(char));
		snprintf(path, PATH_MAX_LEN - 1, VALUE_PATH, pid);

		return IO::readFrom(path, buffer, bufferSize);
	}

	return -1;
}

int GPIOPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	if (direction == OUT) {
		char path[PATH_MAX_LEN];
		memset(path, 0, PATH_MAX_LEN * sizeof(char));
		snprintf(path, PATH_MAX_LEN - 1, VALUE_PATH, pid);

		return IO::writeTo(path, buffer, bufferSize);
	}

	return -1;
}

int GPIOPortBase::exportGPIO() {
	if (!IO::exists(EXPORT_PATH)) {
		return -1;
	}

	char value[VALUE_MAX_LEN];
	memset(value, 0, VALUE_MAX_LEN * sizeof(char));
	snprintf(value, VALUE_MAX_LEN - 1, "%u", pid);

	return IO::writeTo(EXPORT_PATH, (const uint8_t*) value, strlen(value));
}

int GPIOPortBase::unexportGPIO() {
	if (!IO::exists(UNEXPORT_PATH)) {
		return -1;
	}

	char value[VALUE_MAX_LEN];
	memset(value, 0, VALUE_MAX_LEN * sizeof(char));
	snprintf(value, VALUE_MAX_LEN - 1, "%u", pid);

	return IO::writeTo(UNEXPORT_PATH, (const uint8_t*) value, strlen(value));
}

int GPIOPortBase::setDirection(Direction direction) {
	char path[PATH_MAX_LEN];
	memset(path, 0, PATH_MAX_LEN * sizeof(char));
	snprintf(path, PATH_MAX_LEN - 1, DIRECTION_PATH, pid);

	if (!IO::exists(path)) {
		return -1;
	}

	char value[VALUE_MAX_LEN];
	memset(value, 0, VALUE_MAX_LEN * sizeof(char));
	snprintf(value, VALUE_MAX_LEN - 1, "%s", direction == GPIOPortBase::Direction::IN ? "in" : "out");

	int res = IO::writeTo(path, (const uint8_t*) value, strlen(value));
	if (res != -1) {
		this->direction = direction;
	}

	return res;
}

GPIOPortBase::Direction GPIOPortBase::getDirection() {
	return direction;
}

int GPIOPortBase::setValue(uint8_t value) {
	return write(&value, sizeof(uint8_t));
}

int GPIOPortBase::getValue() {
	uint8_t value = 0;
	int res = read(&value, sizeof(uint8_t));

	if (res == -1) {
		return -1;
	}

	return value;
}

uint8_t GPIOPortBase::getPID() {
	return pid;
}
