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
#include <atomic>
#include <thread>
#include <condition_variable>

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
	 * \param[in] info		- connection info
	 * \param[in] connector	- connector
	 */
	Connection(const Info info, IConnectorBase* connector);

	/**
	 * Destructor
	 */
	virtual ~Connection();

	/**
	 * Event callback
	 *
	 * \param[in] event - event
	 */
	void on(const IEvent* event);

	/**
	 * Enable event catching
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int enable();

	/**
	 * Disable event catching
	 *
	 * \return
	 *		- 0 if success
	 *		- -1 if error
	 */
	int disable();

	/**
	 * Get info
	 *
	 * \return connection info
	 */
	Info getInfo();

private:
	Info					info;
	IConnectorBase*			connector		= nullptr;

	std::list<EventWrite*>	eventsList;
	std::mutex				eventsListMutex;
	std::condition_variable	cond;

	std::atomic<bool>		running{false};
	std::atomic<bool>		stopThreads{false};

	std::thread				lazyStart;
	std::thread				readThread;
	std::thread				eventsThread;

	int connect();
	int disconnect();
	int reconnect();
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_CONNECTION_H_ */
