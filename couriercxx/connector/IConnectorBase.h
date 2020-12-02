/*
 * IConnectorBase.h
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_ICONNECTORBASE_H_
#define COURIERCXX_CONNECTOR_ICONNECTORBASE_H_

#include <cstdint>

#include "../Types.h"

/**
 * Base connector interface
 */
class IConnectorBase {
public:
	static const int ERR_DEFAULT;
	static const int ERR_ALREADY_OPEN;
	static const int ERR_NOT_OPEN;
	static const int ERR_TIMEOUT;

	/**
	 * Empty constructor
	 */
	IConnectorBase();

	/**
	 * Copy-constructor
	 */
	IConnectorBase(const IConnectorBase& connector) = default;

	/**
	 * Move constructor
	 */
	IConnectorBase(IConnectorBase&& connector);
	/**
	 * Destructor
	 */
	virtual ~IConnectorBase();

	/**
	 * Copy operator
	 */
	IConnectorBase& operator=(const IConnectorBase& connector) = default;

	/**
	 * Move operator
	 */
	IConnectorBase& operator=(IConnectorBase&& connector);

	/**
	 * Open connector
	 *
	 * \return
	 * 		- 0 - success
	 * 		- -1 - error
	 */
	virtual int open();

	/**
	 * Close connector
	 *
	 * \return
	 * 		- 0 - success
	 * 		- -1 - error
	 */
	virtual int close();

	/**
	 * Check if connector is open
	 *
	 * \return
	 * 		- true - connector is open
	 * 		- false - connector is closed
	 */
	virtual bool isOpen();

	/**
	 * Clear input/output buffers
	 */
	virtual void clear();

	/**
	 * Read data from connector
	 *
	 * \param[out]	buffer		- buffer to store data
	 * \param[in]	bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from connector, wait for timeout msec
	 *
	 * \param[out]	buffer		- buffer to store data
	 * \param[in]	bufferSize	- buffer size
	 * \param[in]	timeout		- read timeout (msec)
	 *
	 * \return
	 * 		- number of read bytes if success
	 * 		- -1 if error or timeout reached
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize, Timeout timeout);

	/**
	 * Write data to connector
	 *
	 * \param[in] buffer		- buffer with data
	 * \param[in] bufferSize	- buffer size
	 *
	 * \return
	 * 		- number of written bytes if success
	 * 		- -1 if error
	 */
	virtual int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	bool opened = false;
};

#endif /* COURIERCXX_CONNECTOR_ICONNECTORBASE_H_ */
