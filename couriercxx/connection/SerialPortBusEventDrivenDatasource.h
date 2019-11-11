/*
 * SerialPortBusEventDrivenDatasource.h
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_SERIALPORTBUSEVENTDRIVENDATASOURCE_H_
#define COURIERCXX_CONNECTION_SERIALPORTBUSEVENTDRIVENDATASOURCE_H_

#include <cstdint>
#include <mutex>

#include "../event/IListener.h"
#include "IDatasource.h"

/**
 * Datasource abstraction
 */
class SerialPortBusEventDrivenDatasource : public IDatasource, public IListener {
public:
	/**
	 * Constructor
	 *
	 * \param[in] uint32_t connectionId
	 */
	SerialPortBusEventDrivenDatasource(uint32_t connectionId);

	/**
	 * Destructor
	 */
	virtual ~SerialPortBusEventDrivenDatasource();

	/**
	 * Enable datasource
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int enable();

	/**
	 * Disable datasource
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int disable();

	/**
	 * Read data
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return int - number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \param[in] int - number of writte bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	uint32_t connectionId = 0;

	uint8_t* tmpBuffer = nullptr;
	uint32_t tmpBufferSize = 0;
	std::mutex accessMutex;

	/**
	 * On event callback
	 *
	 * \param[in] const IEvent* event
	 */
	void on(const IEvent* event);
};

#endif /* COURIERCXX_CONNECTION_SERIALPORTBUSEVENTDRIVENDATASOURCE_H_ */
