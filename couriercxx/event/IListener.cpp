/*
 * IListener.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IListener.h"

IListener::IListener() { }

IListener::IListener(ListenerParams params) {
	this->params = params;
}

IListener::~IListener() { }

bool IListener::operator==(const IListener& listener) {
	return this == &listener;
}

void IListener::on(const IEvent* event) { }

int IListener::enable() {
	enabled = true;

	return 0;
}

int IListener::enable(bool enabled) {
	return enabled ? enable() : disable();
}

int IListener::disable() {
	enabled = false;

	return 0;
}

bool IListener::isEnabled() {
	return enabled;
}

ListenerParams IListener::getParams() {
	return params;
}
