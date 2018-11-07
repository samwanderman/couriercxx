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
	opened = true;

	return 0;
}

int IConnectorBase::close() {
	opened = false;

	return 0;
}

bool IConnectorBase::isOpen() const{
	return opened;
}
