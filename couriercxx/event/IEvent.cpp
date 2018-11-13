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

IEvent::IEvent(EVENT_T type, const IListener* source, const IListener* target) {
	this->type = type;
	this->source = source;
	this->target = target;
}

IEvent::~IEvent() { }

IEvent::IEvent(const IEvent& other) {
	type = other.type;
	source = other.source;
	target = other.target;
}

IEvent::IEvent(IEvent&& other) {
	type = other.type;
	source = other.source;
	target = other.target;
	other.source = nullptr;
	other.target = nullptr;
}

IEvent& IEvent::operator=(const IEvent& other) {
	type = other.type;
	source = other.source;
	target = other.target;

	return *this;
}

IEvent& IEvent::operator=(IEvent&& other) {
	type = other.type;
	source = other.source;
	target = other.target;
	other.source = nullptr;
	other.target = nullptr;

	return *this;
}

EVENT_T IEvent::getType() const {
	return type;
}

const IListener* IEvent::getSource() const {
	return source;
}

const IListener* IEvent::getTarget() const {
	return target;
}

int IEvent::setTarget(const IListener* target) {
	this->target = target;

	return 0;
}

int IEvent::setSource(const IListener* source) {
	this->source = source;

	return 0;
}

EVENT_T IEvent::genEventId() {
	return nextEventId++;
}
