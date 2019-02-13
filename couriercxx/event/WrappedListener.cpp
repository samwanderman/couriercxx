/*
 * WrappedListener.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "WrappedListener.h"

WrappedListener::WrappedListener(std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener() {
	this->listener = listener;
	enable();
}

WrappedListener::WrappedListener(ListenerParams params, std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener(params) {
	this->listener = listener;
	enable();
}

WrappedListener::~WrappedListener() {
	if (listener == nullptr) {
		listener = nullptr;
	}
}

void WrappedListener::on(const IEvent* event) {
	disable();

	if (listener != nullptr) {
		listener(event, this);
	}
}
