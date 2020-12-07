/*
 * Dispatcher.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_DISPATCHER_H_
#define COURIERCXX_EVENT_DISPATCHER_H_

#include <functional>

#include "IEvent.h"

class DispatcherBase;

/**
 * Event dispatcher class for static usage
 */
class Dispatcher {
public:
	/**
	 * Add listener
	 *
	 * \param[in] eventType - event type
	 * \param[in] listener - event listener
	 *
	 * \return 0 if success, -1 if error
	 */
	static int addListener(EVENT_T eventType, IListener* listener);

	/**
	 * Remove listener
	 *
	 * \param[in] eventType - event type
	 * \param[in] listener - event listener
	 *
	 * \return 0 if success, -1 if error
	 */
	static int removeListener(EVENT_T eventType, IListener* listener);

	/**
	 * Trigger an event
	 *
	 * \param[in] const IEvent* event - event
	 */
	static void trigger(const IEvent* event);

	/**
	 * Trigger an event and catch response
	 *
	 * \param[in] IEvent* event - event
	 * \param[in] EVENT_T responseEventType - response event type
	 * \param[in] IListener* listener - listener
	 */
	static void trigger(IEvent* event, EVENT_T responseEventType, IListener* listener);

	/**
	 * Trigger an event and catch response
	 *
	 * \param[in] IEvent* event - event
	 * \param[in] EVENT_T responseEventType - response event type
	 * \param[in] IListener* listener - listener
	 * \param[in] uint32_t timeout - timeout in milliseconds
	 */
	static void trigger(IEvent* event, EVENT_T responseEventType, IListener* listener, uint32_t timeout);

	/**
	 * Wait for event
	 *
	 * \param[in] EVENT_T eventType - type
	 * \param[in] function(const IEvent*) listener - listener
	 */
	static void wait(EVENT_T eventType, std::function<void (const IEvent*)> listener);

	/**
	 * Wait for event
	 *
	 * \param[in] EVENT_T eventType - type
	 * \param[in] function(const IEvent*) listener - listener
	 * \param[in] uint64_t timeout
	 */
	static void wait(EVENT_T eventType, std::function<void (const IEvent*)> listener, uint64_t timeout);

private:
	/**
	 * Get instance of DispatcherBase class
	 */
	static DispatcherBase& getInstance();

};

#endif /* COURIERCXX_EVENT_DISPATCHER_H_ */
