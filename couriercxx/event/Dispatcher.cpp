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

void Dispatcher::trigger(IEvent* event, EVENT_T responseEventType, IListener* listener) {
	event->setSource(listener);
	if (Dispatcher::addListener(responseEventType, listener) == -1) {
		return;
	}

	Dispatcher::trigger(event);
}

void Dispatcher::wait(EVENT_T eventType, std::function<void (const IEvent*)> listener) {
	Dispatcher::getInstance().wait(eventType, listener);
}

void Dispatcher::wait(EVENT_T eventType, std::function<void (const IEvent*)> listener, uint64_t timeout) {
	Dispatcher::getInstance().wait(eventType, listener, timeout);
}

DispatcherBase& Dispatcher::getInstance() {
	static DispatcherBase dispatcher;
	return dispatcher;
}
