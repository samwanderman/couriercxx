/*
 * EventStatus.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_EVENT_EVENTSTATUS_H_
#define COURIERCXX_CONNECTION_EVENT_EVENTSTATUS_H_

#include <cstdint>

#include "../../event/IEvent.h"
#include "EventConnection.h"

namespace Connection {

/**
 * Connection status event
 */
class EventStatus: public IEvent, public EventConnection {
public:
	/**
	 * Constructor
	 *
	 * \param[in] info - connection info
	 * \param[in] status - connection status
	 */
	EventStatus(const Info* info, uint8_t status);

	/**
	 * Constructor
	 *
	 * \param[in] info - connection info
	 * \param[in] status - connection status
	 * \param[in] source - event source
	 * \param[in] target - event target
	 */
	EventStatus(const Info* info, uint8_t status, IListener* source, IListener* target);

	/**
	 * Destructor
	 */
	virtual ~EventStatus();

	/**
	 * Copy-constructor
	 */
	EventStatus(const EventStatus& other);

	/**
	 * Move-constructor
	 */
	EventStatus(EventStatus&& other);

	/**
	 * Copy-operator
	 */
	EventStatus& operator=(const EventStatus& other);

	/**
	 * Move-operator
	 */
	EventStatus& operator=(EventStatus&& other);

	/**
	 * Get connection status
	 *
	 * \return status
	 */
	uint8_t getStatus();

private:
	uint8_t status = 0;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTSTATUS_H_ */
