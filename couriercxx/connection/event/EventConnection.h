/*
 * EventConnection.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_
#define COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_

namespace Connection {
class Info;
} /* namespace Connection */

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
	EventConnection(const Info* info);

	/**
	 * Destructor
	 */
	virtual ~EventConnection();

	/**
	 * Get connection info
	 *
	 * \return connection info
	 */
	const Info* getInfo() const;

private:
	const Info* info = nullptr;
};

}

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTCONNECTION_H_ */
