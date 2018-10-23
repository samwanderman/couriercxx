/*
 * IIEvent.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IEvent.h"

EVENT_T IEvent::nextEventId = 0;

IEvent::IEvent(EVENT_T type) {
	this->type = type;
	this->source = nullptr;
	this->target = nullptr;
}

IEvent::IEvent(EVENT_T type, IListener* source, IListener* target) {
	this->type = type;
	this->source = source;
	this->target = target;
}

IEvent::~IEvent() { }

EVENT_T IEvent::getType() const {
	return type;
}

IListener* IEvent::getSource() const {
	return source;
}

IListener* IEvent::getTarget() {
	return target;
}

int IEvent::setTarget(IListener* target) {
	this->target = target;

	return 0;
}

int IEvent::setSource(IListener* source) {
	this->source = source;

	return 0;
}

EVENT_T IEvent::genEventId() {
	return nextEventId++;
}
