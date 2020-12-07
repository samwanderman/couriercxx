/*
 * SerialPortBaseDatasource.h
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_SERIALPORTBASEDATASOURCE_H_
#define COURIERCXX_CONNECTION_SERIALPORTBASEDATASOURCE_H_

#include <cstdint>

#include "IDatasource.h"

class SerialPortBase;

/**
 * Simple serial port base datasource
 */
class SerialPortBaseDatasource: public IDatasource {
public:
	/**
	 * Constructor
	 *
	 * \param[in] port - serial port
	 *
	 * NOTE: port will be automatically deleted
	 */
	SerialPortBaseDatasource(SerialPortBase* port);

	/**
	 * Destructor
	 */
	virtual ~SerialPortBaseDatasource();

	/**
	 * Enabled datasource
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int enable();

	/**
	 * Disable datasource
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	int disable();

	/**
	 * Read bytes from datasource
	 *
	 * \param[out]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- max buffer size
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read bytes from datasource
	 *
	 * \param[out]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- max buffer size
	 * \param[in]	timeout		- read timeout
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize, uint64_t timeout);

	/**
	 * Write bytes to datasource
	 *
	 * \param[in] buffer		- pointer to buffer
	 * \param[in] bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of written bytes if success
	 * 		- -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	SerialPortBase* port = nullptr;
};

#endif /* COURIERCXX_CONNECTION_SERIALPORTBASEDATASOURCE_H_ */
