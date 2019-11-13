/*
 * SerialPortBusDatasource.h
 *
 *  Created on: 12.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_SERIALPORTBUSDATASOURCE_H_
#define COURIERCXX_CONNECTION_SERIALPORTBUSDATASOURCE_H_

#include <cstdint>

#include "IConcurrentDatasource.h"

class SerialPortBus;

/**
 * Simple serial port bus datasource
 */
class SerialPortBusDatasource: public IConcurrentDatasource {
public:
	/**
	 * Constructor
	 *
	 * \param[in] SerialPortBus* port - port
	 *
	 * NOTE: port will be automatically deleted
	 */
	SerialPortBusDatasource(SerialPortBus* port);

	/**
	 * Destructor
	 */
	virtual ~SerialPortBusDatasource();

	/**
	 * Enabled datasource
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int enable();

	/**
	 * Disable datasource - 0 if success, -1 if error
	 */
	int disable();

	/**
	 * Read bytes from datasource
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max buffer size
	 *
	 * \return int - number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write bytes to datasource
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return int - number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Lock bus
	 */
	void lock();

	/**
	 * Unlock bus
	 */
	void unlock();

private:
	SerialPortBus* port = nullptr;
};

#endif /* COURIERCXX_CONNECTION_SERIALPORTBUSDATASOURCE_H_ */
