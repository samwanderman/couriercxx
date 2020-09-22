/*
 * SerialPortBus.h
 *
 *  Created on: 6.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
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
	 * \param[in] config - config
	 */
	SerialPortBus(SerialPortBase::Config config);

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
