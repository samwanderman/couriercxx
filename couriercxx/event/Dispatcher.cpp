/*
 * Dispatcher.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Dispatcher.h"

#include "DispatcherBase.h"

int Dispatcher::addListener(EVENT_T eventType, IListener* listener) {
	return Dispatcher::getInstance().addListener(eventType, listener);
}

int Dispatcher::removeListener(EVENT_T eventType, IListener* listener) {
	return Dispatcher::getInstance().removeListener(eventType, listener);
}

void Dispatcher::trigger(const IEvent* event) {
	Dispatcher::getInstance().trigger(event);
}

DispatcherBase& Dispatcher::getInstance() {
	static DispatcherBase dispatcher;
	return dispatcher;
}
