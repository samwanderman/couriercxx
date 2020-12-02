/*
 * IDatasource.h
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_IDATASOURCE_H_
#define COURIERCXX_CONNECTION_IDATASOURCE_H_

#include <cstdint>

#include "../Types.h"

/**
 * Datasource interface
 */
class IDatasource {
public:
	/**
	 * Constructor
	 */
	IDatasource() { }

	/**
	 * Destructor
	 */
	virtual ~IDatasource() { };

	/**
	 * Enable datasource
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	virtual int enable() = 0;

	/**
	 * Disable datasource
	 *
	 * \return
	 * 		- 0 if success
	 * 		- -1 if error
	 */
	virtual int disable() = 0;

	/**
	 * Read bytes
	 *
	 * \param[out]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize) = 0;

	/**
	 * Read bytes
	 *
	 * \param[out]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- buffer size
	 * \param[in]	timeout		- timeout
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize, Timeout timeout) = 0;

	/**
	 * Write bytes
	 *
	 * \param[in] buffer		- pointer to buffer
	 * \param[in] bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of written bytes
	 * 		- -1 if error
	 */
	virtual int write(const uint8_t* buffer, uint32_t bufferSize) = 0;
};

#endif /* COURIERCXX_CONNECTION_IDATASOURCE_H_ */
