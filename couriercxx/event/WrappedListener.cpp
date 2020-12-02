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

WrappedListener::WrappedListener(std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener() {
	this->listener = listener;
	enable();
}

WrappedListener::WrappedListener(ListenerParams params, std::function<void (const IEvent*, const WrappedListener*)> listener) : IListener(params) {
	this->listener = listener;
	this->execOnce = params.execOnce;
	enable();

	if (params.timeout > 0) {
		running = true;

		auto timeoutWatcher = [this, params]() {
			while (running) {
				if (Clock::getTimestamp() >= params.timeout) {
					this->on(new EventTimeout());

					break;
				}

				std::this_thread::yield();
			}
		};

		th = std::thread(timeoutWatcher);
	}
}

WrappedListener::~WrappedListener() {
	running = false;

	disable();

	if (th.joinable()) {
		th.join();
	}

	if (listener == nullptr) {
		listener = nullptr;
	}
}

void WrappedListener::on(const IEvent* event) {
	running = false;
	if (execOnce) {
		disable();
	}

	if (listener != nullptr) {
		listener(event, this);
	}
}
