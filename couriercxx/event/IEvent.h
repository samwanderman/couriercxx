/*
 * IEvent.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_EVENT_IEVENT_H_
#define COURIERCXX_EVENT_IEVENT_H_

#include <cstdint>

class IListener;

/**
 * Default event type
 */
typedef uint32_t EVENT_T;

/**
 * Event interface
 */
class IEvent {
public:
	/**
	 * Constructor
	 *
	 * \param[in] type - event type
	 */
	IEvent(EVENT_T type);

	/**
	 * Constructor
	 *
	 * \param[in] type - event type
	 * \param[in] source - initiator of event
	 * \param[in] target - target of event
	 */
	IEvent(EVENT_T type, IListener* source, IListener* target);

	/**
	 * Destructor
	 */
	virtual ~IEvent();

	/**
	 * Get event type
	 *
	 * \return event type
	 */
	EVENT_T getType() const;

	/**
	 * Get target of event
	 *
	 * \return pointer to target
	 */
	IListener* getTarget();

	/**
	 * Set target of event
	 *
	 * \param[in] target - target of event
	 *
	 * \return 0 if success, -1 if error
	 */
	int setTarget(IListener* target);

	/**
	 * Get source of event
	 *
	 * \return pointer to event source
	 */
	IListener* getSource() const;

	/**
	 * Set source of event
	 *
	 * \param[in] source - source of event
	 *
	 * \return 0 if success, -1 if error
	 */
	int setSource(IListener* source);

	/**
	 * Generate new event UID
	 *
	 * \return uid
	 */
	static EVENT_T genEventId();

private:
	static EVENT_T nextEventId;

	EVENT_T type;
	IListener* source = nullptr;
	IListener* target = nullptr;
};

#endif /* COURIERCXX_EVENT_IEVENT_H_ */
