/*
 * DispatcherBase.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "DispatcherBase.h"

#include <algorithm>
#include <utility>

#include "../logger/Log.h"

DispatcherBase::DispatcherBase() { }

DispatcherBase::~DispatcherBase() {
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
	Log::debug("Events.addListener(%x)", listener);
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
	Log::debug("Events.removeListener(%x)", listener);
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
	Log::debug("Events.trigger()", event->getType());
	std::list<IListener*>* foundListeners = getListeners(event->getType());
	if ((foundListeners == nullptr) || (foundListeners->size() == 0)) {
		return;
	}

	std::list<IListener*> l(*foundListeners);
	std::list<IListener*>::iterator it = l.begin();
	while (it != l.end()) {
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
