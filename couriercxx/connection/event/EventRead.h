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
#include "../Info.h"
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
	 * \param[in] const Info info - connection info
	 * \param[in] const uint8_t* data - pointer to data
	 * \param[in] uint32_t dataSize - max data size
	 */
	EventRead(const Info info, const uint8_t* data, uint32_t dataSize);

	/**
	 * Constructor
	 *
	 * \param[in] const Info info - connection info
	 * \param[in] const uint8_t* data - pointer to data
	 * \param[in] uint32_t dataSize - max data size
	 * \param[in] IListener* source - event source
	 * \param[in] IListener* target - event target
	 */
	EventRead(const Info info, const uint8_t* data, uint32_t dataSize, IListener* source, IListener* target);

	/**
	 * Copy-constructor
	 *
	 * \param[in] const EventRead& other - other object
	 */
	EventRead(const EventRead& other);

	/**
	 * Move-constructor
	 *
	 * \param[in] EventRead& other - other object
	 */
	EventRead(EventRead&& other);

	/**
	 * Destructor
	 */
	virtual ~EventRead();

	/**
	 * Operator= overloading
	 *
	 * \param[in] const EventRead& other - other object
	 *
	 * \return EventRead& - this
	 */
	EventRead& operator=(const EventRead& other);

	/**
	 * Operator= overloading
	 *
	 * \param[in] EventRead&& other - other object
	 *
	 * \return EventRead& - this
	 */
	EventRead& operator=(EventRead&& other);

	/**
	 * Get data size
	 *
	 * \return uint32_t - data size
	 */
	uint32_t getDataSize() const;

	/**
	 * Copy data to buffer
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t buferSize - max buffer size
	 *
	 * \return int - bytes in data if success, -1 if error
	 */
	int getData(uint8_t* buffer, uint32_t bufferSize) const;

	/**
	 * Get raw pointer to data
	 *
	 * \return const uint8_t* - pointer to data
	 */
	const uint8_t* getData() const;

private:
	uint8_t* data		= nullptr;
	uint32_t dataSize	= 0;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTREAD_H_ */
