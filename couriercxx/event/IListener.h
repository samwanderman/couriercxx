/*
 * IListener.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_ILISTENER_H_
#define COURIERCXX_EVENT_ILISTENER_H_

#include "ListenerParams.h"

struct ListenerParams;
class IEvent;

/**
 * Class-listener interface
 */
class IListener {
public:
	/**
	 * Constructor
	 */
	IListener();

	/**
	 * Constructor
	 *
	 * \param[in] ListenerParams params - listener params
	 */
	IListener(ListenerParams params);

	/**
	 * Destructor
	 */
	virtual ~IListener();

	/**
	 * Operator== overloading
	 *
	 * \param[in] listener - pointer to another listener
	 */
	bool operator==(const IListener& listener);

	/**
	 * Callback on event appearance
	 *
	 * \param[in] event - event
	 */
	virtual void on(const IEvent* event);

	/**
	 * Enable event catching
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int enable();

	/**
	 * Enable/disable event catching
	 *
	 * \param[in] bool enabled - enable/disable
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int enable(bool enabled);

	/**
	 * Disable event catching
	 */
	virtual int disable();

	/**
	 * Check if event catch is enabled
	 *
	 * \return true if enabled, false is disabled
	 */
	virtual bool isEnabled();

	/**
	 * Get listener params
	 *
	 * \return ListenerParams params
	 */
	ListenerParams getParams();

protected:
	bool enabled = false;
	ListenerParams params;
};

#endif /* COURIERCXX_EVENT_ILISTENER_H_ */
