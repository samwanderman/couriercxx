/*
 * IConnectorBase.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IConnectorBase.h"

IConnectorBase::IConnectorBase() { }

IConnectorBase::~IConnectorBase() { }

int IConnectorBase::open() {
	if (isOpen()) {
		return -1;
	}

	opened = true;

	return 0;
}

int IConnectorBase::close() {
	if (!isOpen()) {
		return -1;
	}

	opened = false;

	return 0;
}

bool IConnectorBase::isOpen() {
	return opened;
}

int IConnectorBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return isOpen() ? 0 : -1;
}

int IConnectorBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	return isOpen() ? 0 : -1;
}
