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

#include "../util/Clock.h"

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
	static const EVENT_T EVENT_TIMEOUT;

	/**
	 * Constructor
	 *
	 * \param[in] type - event type
	 */
	IEvent(EVENT_T type);

	/**
	 * Constructor
	 *
	 * \param[in] EVENT_T type - event type
	 * \param[in] const IListener* source - initiator of event
	 * \param[in] const IListener* target - target of event
	 */
	IEvent(EVENT_T type, const IListener* source, const IListener* target);

	/**
	 * Destructor
	 */
	virtual ~IEvent();

	/**
	 * Copy-constructor
	 */
	IEvent(const IEvent& other);

	/**
	 * Move-constructor
	 */
	IEvent(IEvent&& other);

	/**
	 * Copy operator overload
	 */
	IEvent& operator=(const IEvent& other);

	/**
	 * Move operator overload
	 */
	IEvent& operator=(IEvent&& event);

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
	const IListener* getTarget() const;

	/**
	 * Set target of event
	 *
	 * \param[in] const IListener* target - target of event
	 *
	 * \return 0 if success, -1 if error
	 */
	int setTarget(const IListener* target);

	/**
	 * Get source of event
	 *
	 * \return pointer to event source
	 */
	const IListener* getSource() const;

	/**
	 * Set source of event
	 *
	 * \param[in] const IListener* source - source of event
	 *
	 * \return 0 if success, -1 if error
	 */
	int setSource(const IListener* source);

	/**
	 * Generate new event UID
	 *
	 * \return uid
	 */
	static EVENT_T genEventId();

	/**
	 * Get event creation timestamp
	 *
	 * \return timestamp
	 */
	uint64_t getCreationTimestamp() const;

private:
	static EVENT_T nextEventId;

	EVENT_T type;
	const IListener* source = nullptr;
	const IListener* target = nullptr;

	uint64_t timestamp = Clock::getTimestamp();
};

#endif /* COURIERCXX_EVENT_IEVENT_H_ */
