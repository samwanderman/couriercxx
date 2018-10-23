/*
 * SerialPortBase.h
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBASE_H_
#define COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBASE_H_

#include <cstdint>
#include <string>

#include "../../../couriercxx/connector/IConnectorBase.h"

/**
 * Serial port base class
 */
class SerialPortBase: public IConnectorBase {
public:
	/**
	 * Base serial port constructor
	 *
	 * \param[in] string name - port system name
	 */
	SerialPortBase(std::string name);

	/**
	 * Base serial port constructor
	 *
	 * \param[in] string name - port system name
	 * \param[in] uint32_t speed - port speed
	 */
	SerialPortBase(std::string name, uint32_t speed);

	SerialPortBase(const SerialPortBase& port) = default;
	SerialPortBase(SerialPortBase&& port) = default;

	/**
	 * Base serial port destructor
	 */
	~SerialPortBase();

	SerialPortBase& operator=(const SerialPortBase& port) = default;
	SerialPortBase& operator=(SerialPortBase&& port) = default;

	/**
	 * Open serial port
	 *
	 * \return 0 - success, -1 - error
	 */
	int open();

	/**
	 * Close serial port
	 *
	 * \return 0 - success, -1 - error
	 */
	int close();

	/**
	 * Read data from serial port
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to serial port
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	std::string name = "";
	uint32_t speed = 0;
	int fd = -1;
};

#endif /* COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBASE_H_ */
