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
#include "../Info.h"
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
	 * \param[in] const Info info - connection info
	 * \param[in] uint8_t status - connection status
	 */
	EventStatus(const Info info, uint8_t status);

	/**
	 * Constructor
	 *
	 * \param[in] const Info info - connection info
	 * \param[in] uint8_t status - connection status
	 * \param[in] IListener* source - event source
	 * \param[in] IListener* target - event target
	 */
	EventStatus(const Info info, uint8_t status, IListener* source, IListener* target);

	/**
	 * Destructor
	 */
	virtual ~EventStatus();

	/**
	 * Get connection status
	 *
	 * \return uint8_t - status
	 */
	uint8_t getStatus();

private:
	uint8_t status = 0;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTSTATUS_H_ */
