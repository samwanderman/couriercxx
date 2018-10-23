/*
 * IListener.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_ILISTENER_H_
#define COURIERCXX_EVENT_ILISTENER_H_

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
	 * Destructor
	 */
	virtual ~IListener() = 0;

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

protected:
	bool enabled = false;
};

#endif /* COURIERCXX_EVENT_ILISTENER_H_ */
