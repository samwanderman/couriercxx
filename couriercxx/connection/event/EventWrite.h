/*
 * EventWrite.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_EVENT_EVENTWRITE_H_
#define COURIERCXX_CONNECTION_EVENT_EVENTWRITE_H_

#include <cstdint>

#include "../../event/IEvent.h"
#include "../Info.h"
#include "EventConnection.h"

namespace Connection {

/**
 * Connection write event
 */
class EventWrite: public IEvent, public EventConnection {
public:
	/**
	 * Constructor
	 *
	 * \param[in] const Info info - connection info
	 * \param[in] const uint8_t* data - pointer to data
	 * \param[in] uint32_t dataLen - max data size
	 */
	EventWrite(const Info info, const uint8_t* data, uint32_t dataLen);

	/**
	 * Constructor
	 *
	 * \param[in] const Info info - connection info
	 * \param[in] const uint8_t* data - pointer to data
	 * \param[in] uint32_t dataLen - max data size
	 * \param[in] IListener* source - event source
	 * \param[in] IListener* target - event target
	 */
	EventWrite(const Info info, const uint8_t* data, uint32_t dataLen, IListener* source, IListener* target);

	/**
	 * Copy-constructor
	 *
	 * \param[in] const EventWrite& other - other object
	 */
	EventWrite(const EventWrite& other);

	/**
	 * Move-constructor
	 *
	 * \param[in] EventWrite&& other - other object
	 */
	EventWrite(EventWrite&& other);

	/**
	 * Destructor
	 */
	virtual ~EventWrite();

	/**
	 * Operator= overloading
	 *
	 * \param[in] const EventWrite& other - other object
	 *
	 * \return EventWrite& - this
	 */
	EventWrite& operator=(const EventWrite& other);

	/**
	 * Operator= overloading
	 *
	 * \param[in] EventWrite&& other - other object
	 *
	 * \return EventWrite& - this
	 */
	EventWrite& operator=(EventWrite&& other);

	/**
	 * Get data length
	 *
	 * \return uint32_t data len
	 */
	uint32_t getDataLen() const;

	/**
	 * Copy data to buffer
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t buferSize - max buffer size
	 *
	 * \return int - number of bytes in data if success, -1 if error
	 */
	int getData(uint8_t* buffer, uint32_t bufferSize) const;

	/**
	 * Get raw pointer to data
	 *
	 * \return const uint8_t* - pointer to data
	 */
	const uint8_t* getData() const;

private:
	uint8_t* data = nullptr;
	uint32_t dataLen = 0;
};

} /* namespace Connection */

#endif /* COURIERCXX_CONNECTION_EVENT_EVENTWRITE_H_ */
