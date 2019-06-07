/*
 * EventConnection.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_
#define COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_

#include "../Info.h"

namespace Connection {

/**
 * Base class for connection events
 */
class EventConnection {
public:
	/**
	 * Constructor
	 *
	 * \param info - connection info
	 */
	EventConnection(const Info info);

	/**
	 * Destructor
	 */
	virtual ~EventConnection();

	/**
	 * Get connection info
	 *
	 * \return const Info - connection info
	 */
	const Info getInfo() const;

private:
	Info info;
};

}

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_ */
