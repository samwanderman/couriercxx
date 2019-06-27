/*
 * WrappedListener.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "WrappedListener.h"

#include <cstdint>
#include <thread>

#include "../util/Clock.h"
#include "../util/System.h"
#include "event/EventTimeout.h"
#include "ListenerParams.h"

#define TIMEOUT	200

WrappedListener::WrappedListener(std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener() {
	this->listener = listener;
	enable();
}

WrappedListener::WrappedListener(ListenerParams params, std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener(params) {
	this->listener = listener;
	enable();

	if (params.timeout != (uint64_t) ~0) {
		running = true;

		auto timeoutWatcher = [this, params]() {
			stopLock.lock();

			while (running) {
				if (Clock::getTimestamp() >= params.timeout) {
					this->on(new EventTimeout());

					break;
				}

				System::sleep(TIMEOUT);
			}

			stopLock.unlock();
		};

		std::thread th(timeoutWatcher);
		th.detach();
	}
}

WrappedListener::~WrappedListener() {
	running = false;

	// If timeout thread running - wait while it complete
	stopLock.lock();

	if (listener == nullptr) {
		listener = nullptr;
	}
}

void WrappedListener::on(const IEvent* event) {
	running = false;
	disable();

	if (listener != nullptr) {
		listener(event, this);
	}
}
