/*
 * DispatcherBase.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_DISPATCHERBASE_H_
#define COURIERCXX_EVENT_DISPATCHERBASE_H_

#include <list>
#include <map>
#include <mutex>

#include "IEvent.h"
#include "IListener.h"

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
	 * \param[in] eventType - event type
	 * \param[in] listener - event listener
	 *
	 * \return 0 if success, -1 if error
	 */
	int addListener(EVENT_T eventType, IListener* listener);

	/**
	 * Remove listener
	 *
	 * \param[in] eventType - event type
	 * \param[in] listener - event listener
	 *
	 * \return 0 if success, -1 if error
	 */
	int removeListener(EVENT_T eventType, IListener* listener);

	/**
	 * Trigger an event
	 *
	 * \param[in] event - event
	 */
	void trigger(IEvent* event);

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
};

#endif /* COURIERCXX_EVENT_DISPATCHERBASE_H_ */
