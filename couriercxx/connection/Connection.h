/*
 * Connection.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_CONNECTION_H_
#define COURIERCXX_CONNECTION_CONNECTION_H_

#include <list>
#include <mutex>

#include "../event/IEvent.h"
#include "../event/IListener.h"
#include "event/EventWrite.h"
#include "Info.h"

class IConnectorBase;

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
	 * \param[in] const Info info - connection info
	 * \param[in] IConnectorBase* connector - connector
	 */
	Connection(const Info info, IConnectorBase* connector);

	/**
	 * Destructor
	 */
	virtual ~Connection();

	/**
	 * Event callback
	 *
	 * \param[in] const IEvent* event
	 */
	void on(const IEvent* event);

	/**
	 * Enable event catching
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int enable();

	/**
	 * Disable event catching
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int disable();

private:
	Info info;
	IConnectorBase* connector = nullptr;
	bool readThreadRunning = false;
	bool eventsThreadRunning = false;
	std::list<EventWrite*> eventsList;
	std::mutex eventsListMutex;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_CONNECTION_H_ */
