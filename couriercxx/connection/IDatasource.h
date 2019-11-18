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
	 * \return int - 0 if success, -1 if error
	 */
	virtual int enable() = 0;

	/**
	 * Disable datasource
	 *
	 * \return int - 0 if success, -1 if error
	 */
	virtual int disable() = 0;

	/**
	 * Read bytes
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return int - number of read bytes if success, -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize) = 0;

	/**
	 * Read bytes
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 * \param[in] uint64_t timeout - timeout
	 *
	 * \return int - number of read bytes if success, -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize, uint64_t timeout) = 0;

	/**
	 * Write bytes
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return int - number of written bytes, -1 if error
	 */
	virtual int write(const uint8_t* buffer, uint32_t bufferSize) = 0;
};

#endif /* COURIERCXX_CONNECTION_IDATASOURCE_H_ */
