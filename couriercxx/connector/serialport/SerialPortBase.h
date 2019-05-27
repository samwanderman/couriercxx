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

#include "../IConnectorBase.h"

/**
 * Serial port base class
 */
class SerialPortBase: public IConnectorBase {
public:
	/**
	 * Serial port configuration struct
	 */
	struct Config {
		std::string name = "";
		uint32_t baudrate = 0;
		bool nonBlock = false;
		uint32_t timeout = 0;
	};
	typedef struct Config Config;

	/**
	 * Serial port constructor
	 *
	 * \param[in] Config config - configuration
	 */
	SerialPortBase(Config config);

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

	/**
	 * Base serial port constructor
	 *
	 * \param[in] string name - port system name
	 * \param[in] uint32_t speed - port speed
	 * \param[in] uint32_t timeout - port IO timeout
	 */
	SerialPortBase(std::string name, uint32_t speed, uint32_t timeout);

	/**
	 * Copy constructor
	 */
	SerialPortBase(const SerialPortBase& port) = default;

	/**
	 * Move constructor
	 */
	SerialPortBase(SerialPortBase&& port);

	/**
	 * Base serial port destructor
	 */
	~SerialPortBase();

	/**
	 * Copy operator
	 */
	SerialPortBase& operator=(const SerialPortBase& port) = default;

	/**
	 * Move operator
	 */
	SerialPortBase& operator=(SerialPortBase&& port);

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
	 * Read data from serial port
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - size of buffer
	 * \param[in] int32_t timeout - timeout in msec
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize, int32_t timeout);

	/**
	 * Write data to serial port
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Set port speed
	 *
	 * \param[in] uint32_t speed - speed
	 *
	 * \return 0 if success, -1 if error
	 */
	int setBaudrate(uint32_t baudrate);

	/**
	 * Get current port speed
	 *
	 * \return port speed
	 */
	uint32_t getBaudrate();

private:
	Config config;
	int fd = -1;

	void clean();
};

#endif /* COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBASE_H_ */
