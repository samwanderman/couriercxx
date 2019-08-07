/*
 * DispatcherBase.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "DispatcherBase.h"

#include <algorithm>
#include <cstdint>
#include <thread>
#include <utility>

#include "../logger/Log.h"
#include "../util/Clock.h"
#include "../util/System.h"
#include "event/EventTimeout.h"
#include "ListenerParams.h"
#include "WrappedListener.h"

#define EVENT_WATCHER_TIMEOUT	1000

DispatcherBase::DispatcherBase() {
	stopMutex.unlock();
	running = true;

	// timeout watcher
	auto func = [this]() {
		const EventTimeout eventTimeout;

		stopMutex.lock();

		while (running) {
			uint64_t now = Clock::getTimestamp();

			// iterate through listeners for different events
			std::map<EVENT_T, std::list<IListener*>*>::iterator it = listeners.begin();
			while (it != listeners.end()) {
				std::list<IListener*>* listeners2 = it->second;

				std::list<IListener*> l(*listeners2);
				std::list<IListener*>::iterator it2 = l.begin();

				// iterate through listeners for same event
				while (it2 != l.end()) {
					IListener* listener = *it2;
					ListenerParams params = listener->getParams();

					if (params.timeout < now) {
						listener->on(&eventTimeout);
					}

					it2++;
				}

				it++;
			}

			System::sleep(EVENT_WATCHER_TIMEOUT);
		}

		stopMutex.unlock();
	};
	std::thread th(func);
	th.detach();
}

DispatcherBase::~DispatcherBase() {
	running = false;

	stopMutex.lock();

	listenerMutex.lock();

	std::map<EVENT_T, std::list<IListener*>*>::iterator it = listeners.begin();
	while (it != listeners.end()) {
		std::list<IListener*>* listeners2 = it->second;
		listeners2->empty();
		delete listeners2;

		it++;
	}

	listeners.empty();

	listenerMutex.unlock();
}

int DispatcherBase::addListener(EVENT_T eventType, IListener* listener) {
	Log::debug("DispatcherBase.addListener(%x)", listener);
	listenerMutex.lock();
	std::list<IListener*>* foundListeners = getListeners(eventType);
	bool eventExists = foundListeners != nullptr;
	if (eventExists) {
		// check if same listener exists
		std::list<IListener*>::iterator it2 = std::find(foundListeners->begin(), foundListeners->end(), listener);
		if (it2 != foundListeners->end()) {
			listenerMutex.unlock();

			return -1;
		}
	} else {
		foundListeners = new std::list<IListener*>();
	}
	foundListeners->push_back(listener);

	if (!eventExists) {
		listeners.insert(std::pair<EVENT_T, std::list<IListener*>*>(eventType, foundListeners));
	}

	listenerMutex.unlock();

	return 0;
}

int DispatcherBase::removeListener(EVENT_T eventType, IListener* listener) {
	Log::debug("DispatcherBase.removeListener(%x)", listener);
	listenerMutex.lock();

	std::list<IListener*>* foundListeners = getListeners(eventType);
	bool eventExists = foundListeners != nullptr;
	if (!eventExists) {
		listenerMutex.unlock();

		return -1;
	}

	// check if listener exists
	std::list<IListener*>::iterator it2 = std::find(foundListeners->begin(), foundListeners->end(), listener);
	if (it2 == foundListeners->end()) {
		listenerMutex.unlock();

		return -1;
	}

	foundListeners->remove(listener);
	if (foundListeners->size() == 0) {
		listeners.erase(eventType);
		delete foundListeners;
	}

	listenerMutex.unlock();

	return 0;
}

void DispatcherBase::trigger(const IEvent* event) {
//	Log::debug("DispatcherBase.trigger()", event->getType());
	std::list<IListener*>* foundListeners = getListeners(event->getType());
	if ((foundListeners == nullptr) || (foundListeners->size() == 0)) {
//		Log::error("Listener not found");

		delete event;

		return;
	}

	std::list<IListener*> l(*foundListeners);
	std::list<IListener*>::iterator it = l.begin();
	while (it != l.end()) {
//		Log::debug("IListener.isEnabled() %i", (*it)->isEnabled());
		if ((*it)->isEnabled() && ((event->getTarget() == nullptr) || (event->getTarget() == *it))) {
			(*it)->on(event);
		}

		it++;
	}

	delete event;
}

std::list<IListener*>* DispatcherBase::getListeners(EVENT_T eventType) {
	std::map<EVENT_T, std::list<IListener*>*>::iterator it = listeners.find(eventType);
	if (it == listeners.end()) {
		return nullptr;
	} else {
		return it->second;
	}
}

void DispatcherBase::wait(EVENT_T eventType, std::function<void (const IEvent*)> listener) {
	addListener(eventType, new WrappedListener([this, eventType, listener](const IEvent* event, const WrappedListener* self) {
		listener(event);
		removeListener(eventType, (IListener*) self);
	}));
}

void DispatcherBase::wait(EVENT_T eventType, std::function<void (const IEvent*)> listener, uint64_t timeout) {
	ListenerParams param;
	param.timeout = Clock::getTimestamp() + timeout;
	addListener(eventType, new WrappedListener(param, [this, eventType, listener](const IEvent* event, const WrappedListener* self) {
		listener(event);
		removeListener(eventType, (IListener*) self);
	}));
}
