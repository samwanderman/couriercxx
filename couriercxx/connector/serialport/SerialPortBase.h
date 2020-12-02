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

#ifdef _WIN32
#include <windows.h>
#endif

#include "../IConnectorBase.h"
#include "../../Types.h"

/**
 * Serial port base class
 */
class SerialPortBase: public IConnectorBase {
public:
	/**
	 * Serial port configuration struct
	 */
	struct Config {
		std::string	path		= "";
		uint32_t	baudrate	= 0;
		bool		nonBlock	= false;
		Timeout		timeout		= -1;
		bool		parityCheck	= false;
		bool		stopBit		= false;
		bool		startBit	= false;
		bool		handshake	= false;
		uint8_t		dataBits	= 8;
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
	 * \param[in] string path - path to port
	 */
	SerialPortBase(std::string path);

	/**
	 * Base serial port constructor
	 *
	 * \param[in] string path - path to port
	 * \param[in] uint32_t baudrate- port baudrate
	 */
	SerialPortBase(std::string path, uint32_t baudrate);

	/**
	 * Base serial port constructor
	 *
	 * \param[in] path		- path to port
	 * \param[in] baudrate	- port baudrate
	 * \param[in] timeout	- port IO timeout
	 */
	SerialPortBase(std::string path, uint32_t baudrate, Timeout timeout);

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
	virtual int open();

	/**
	 * Close serial port
	 *
	 * \return 0 - success, -1 - error
	 */
	virtual int close();

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
	 * \param[out]	buffer		- buffer to store data
	 * \param[in]	bufferSize	- size of buffer
	 * \param[in]	timeout		- timeout in msec
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize, Timeout timeout);

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
	 * Set port baudrate
	 *
	 * \param[in] uint32_t baudrate- baudrate
	 *
	 * \return 0 if success, -1 if error
	 */
	int setBaudrate(uint32_t baudrate);

	/**
	 * Get current port baudrate
	 *
	 * \return port baudrate
	 */
	uint32_t getBaudrate();

	/**
	 * Clear input/output buffers
	 */
	void clear();

	/**
	 * Check if descriptor is still valid
	 *
	 * \return true if descriptor is valid, false - otherwise
	 */
	bool isValid();

private:
	Config config;

#ifdef _WIN32
	HANDLE fd = nullptr;
#else
	int fd = -1;
#endif

	void clean();
};

#endif /* COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBASE_H_ */
