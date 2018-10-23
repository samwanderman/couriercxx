/*
 * EventRead.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_EVENT_EVENTREAD_H_
#define COURIERCXX_CONNECTION_EVENT_EVENTREAD_H_

#include <cstdint>

#include "../../event/IEvent.h"
#include "EventConnection.h"

namespace Connection {

/**
 * Connection read event
 */
class EventRead: public IEvent, public EventConnection {
public:
	/**
	 * Constructor
	 *
	 * \param[in] info - connection info
	 * \param[in] data - pointer to data
	 * \param[in] dataLen - max data size
	 */
	EventRead(const Info* info, const uint8_t* data, uint32_t dataLen);

	/**
	 * Constructor
	 *
	 * \param[in] info - connection info
	 * \param[in] data - pointer to data
	 * \param[in] dataLen - max data size
	 * \param[in] source - event source
	 * \param[in] target - event target
	 */
	EventRead(const Info* info, const uint8_t* data, uint32_t dataLen, IListener* source, IListener* target);

	/**
	 * Copy-constructor
	 *
	 * \param[in] other - other object
	 */
	EventRead(const EventRead& other);

	/**
	 * Move-constructor
	 *
	 * \param[in] other - other object
	 */
	EventRead(EventRead&& other);

	/**
	 * Destructor
	 */
	virtual ~EventRead();

	/**
	 * Operator= overloading
	 *
	 * \param[in] other - other object
	 */
	EventRead& operator=(const EventRead& other);

	/**
	 * Operator= overloading
	 *
	 * \param[in] other - other object
	 */
	EventRead& operator=(EventRead&& other);

	/**
	 * Get data length
	 *
	 * \return data len
	 */
	uint32_t getDataLen();

	/**
	 * Copy data to buffer
	 *
	 * \param[out] buffer - pointer to buffer
	 * \param[in] buferSize - max buffer size
	 */
	int getData(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Get raw pointer to data
	 *
	 * \return pointer to data
	 */
	uint8_t* getData();

private:
	uint8_t* data = nullptr;
	uint32_t dataLen= 0;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTREAD_H_ */
