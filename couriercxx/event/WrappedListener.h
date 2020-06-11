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
#include <mutex>

#include "IEvent.h"
#include "IListener.h"

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
	WrappedListener(std::function<void (const IEvent*, const WrappedListener*)> listener);

	/**
	 * Constructor
	 *
	 * \param[in] ListenerParams params - params
	 * \param[in] listener - callback function
	 */
	WrappedListener(ListenerParams params, std::function<void (const IEvent*, const WrappedListener*)> listener);

	/**
	 * Destructor
	 */
	virtual ~WrappedListener();

	/**
	 * Event callback
	 *
	 * \param[in] IEvent* event - event
	 */
	virtual void on(const IEvent* event);

private:
	std::function<void (const IEvent*, const WrappedListener*)> listener = nullptr;

	bool		running		= false;
	std::mutex	stopMutex;
	bool		execOnce	= true;
};

#endif /* COURIERCXX_EVENT_WRAPPEDLISTENER_H_ */
