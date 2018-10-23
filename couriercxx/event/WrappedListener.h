/*
 * WrappedListener.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_WRAPPEDLISTENER_H_
#define COURIERCXX_EVENT_WRAPPEDLISTENER_H_

#include <functional>

#include "../../couriercxx/event/IEvent.h"
#include "../../couriercxx/event/IListener.h"

/**
 * Wrapped listener for callback functionality simplification
 */
class WrappedListener : public IListener {
public:
	/**
	 * Constructor
	 *
	 * \param[in] listener - callback function
	 */
	WrappedListener(std::function<void (IEvent*, WrappedListener*)> listener);

	/**
	 * Destructor
	 */
	virtual ~WrappedListener();

	/**
	 * Event callback
	 *
	 * \param[in] IEvent* event - event
	 */
	virtual void on(IEvent* event);

private:
	std::function<void (IEvent*, WrappedListener*)> listener = nullptr;
};

#endif /* COURIERCXX_EVENT_WRAPPEDLISTENER_H_ */
