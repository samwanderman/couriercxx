/*
 * SerialPortBus.h
 *
 *  Created on: 6.11.2019
 *      Author: Potapov Sergei
 *       Email: potapov.sa@carddex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBUS_H_
#define COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBUS_H_

#include <cstdint>
#include <mutex>
#include <string>

#include "SerialPortBase.h"

/**
 * Class for serial port bus
 */
class SerialPortBus : public SerialPortBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string path - path to port
	 * \param[in] uint32_t baudrate - port baudrate
	 */
	SerialPortBus(std::string path, uint32_t baudrate);

	/**
	 * Destructor
	 */
	virtual ~SerialPortBus();

	/**
	 * Lock bus
	 */
	void lock();

	/**
	 * Unlock bus
	 */
	void unlock();

private:
	std::mutex accessMutex;
};

#endif /* COURIERCXX_CONNECTOR_SERIALPORT_SERIALPORTBUS_H_ */
