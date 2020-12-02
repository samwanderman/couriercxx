/*
 * DispatcherBase.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_DISPATCHERBASE_H_
#define COURIERCXX_EVENT_DISPATCHERBASE_H_

#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <thread>

#include "IEvent.h"
#include "IListener.h"
#include "../Types.h"

/**
 * Event dispatcher class
 */
class DispatcherBase {
public:
	/**
	 * Constructor
	 */
	DispatcherBase();

	/**
	 * Destructor
	 */
	virtual ~DispatcherBase();

	/**
	 * Add listener
	 *
	 * \param[in] EVENT_T eventType - type
	 * \param[in] IListener* listener - listener
	 *
	 * \return 0 if success, -1 if error
	 */
	int addListener(EVENT_T eventType, IListener* listener);

	/**
	 * Remove listener
	 *
	 * \param[in] EVENT_T eventType - type
	 * \param[in] IListener* listener - listener
	 *
	 * \return 0 if success, -1 if error
	 */
	int removeListener(EVENT_T eventType, IListener* listener);

	/**
	 * Trigger an event
	 *
	 * \param[in] const IEvent* event - event to send
	 */
	void trigger(const IEvent* event);

	/**
	 * Wait for event
	 *
	 * \param[in] EVENT_T eventType - type
	 * \param[in] function(const IEvent*) listener - listener
	 */
	void wait(EVENT_T eventType, std::function<void (const IEvent*)> listener);

	/**
	 * Wait for event with timeout
	 *
	 * \param[in] eventType	- type
	 * \param[in] listener	- listener
	 * \param[in] timeout	- timeout
	 */
	void wait(EVENT_T eventType, std::function<void (const IEvent*)> listener, Timeout timeout);


private:
	std::map<EVENT_T, std::list<IListener*>*> listeners;
	std::mutex listenerMutex;

	/**
	 * Get listeners for event type
	 *
	 * \param[in] EVENT_T eventType - event type
	 *
	 * \return list of listeners if success, nullptr if error
	 */
	std::list<IListener*>* getListeners(EVENT_T eventType);
	bool running = false;
	std::thread th;
};

#endif /* COURIERCXX_EVENT_DISPATCHERBASE_H_ */
