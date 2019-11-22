/*
 * IConnectorBase.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IConnectorBase.h"

const int IConnectorBase::ERR_DEFAULT		= -1;
const int IConnectorBase::ERR_ALREADY_OPEN	= -2;
const int IConnectorBase::ERR_NOT_OPEN		= -3;

IConnectorBase::IConnectorBase() { }

IConnectorBase::IConnectorBase(IConnectorBase&& other) {
	this->opened = other.opened;
}

IConnectorBase& IConnectorBase::operator=(IConnectorBase&& other) {
	this->opened = other.opened;
	return *this;
}

IConnectorBase::~IConnectorBase() { }

int IConnectorBase::open() {
	opened = true;

	return 0;
}

int IConnectorBase::close() {
	opened = false;

	return 0;
}

bool IConnectorBase::isOpen() {
	return opened;
}

int IConnectorBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}

int IConnectorBase::read(uint8_t* buffer, uint32_t bufferSize, uint32_t timeout) {
	return read(buffer, bufferSize);
}

int IConnectorBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}
