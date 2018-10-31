/*
 * Connection.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_CONNECTION_H_
#define COURIERCXX_CONNECTION_CONNECTION_H_

#include "../event/IEvent.h"
#include "../event/IListener.h"

class IConnectorBase;

namespace Connection {
class Info;
} /* namespace Connection */

namespace Connection {

/**
 * Connection class
 */
class Connection : public IListener {
public:
	static const EVENT_T EVENT_READ;
	static const EVENT_T EVENT_WRITE;
	static const EVENT_T EVENT_STATUS;

	/**
	 * Constructor
	 *
	 * \param[in] info - connection info
	 * \param[in] connector - connector
	 */
	Connection(const Info* info, IConnectorBase* connector);

	/**
	 * Destructor
	 */
	virtual ~Connection();

	/**
	 * Event callback
	 */
	void on(const IEvent* event);

	/**
	 * Enable event catching
	 *
	 * \return 0 if success, -1 if error
	 */
	int enable();

	/**
	 * Disable event catching
	 *
	 * \return 0 if success, -1 if error
	 */
	int disable();

private:
	const Info* info = nullptr;
	IConnectorBase* connector = nullptr;
	bool readThreadRunning = false;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_CONNECTION_H_ */
