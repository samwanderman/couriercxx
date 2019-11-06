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

/**
 * Base connector interface
 */
class IConnectorBase {
public:
	static const uint8_t ERR_DEFAULT;
	static const uint8_t ERR_ALREADY_OPEN;
	static const uint8_t ERR_NOT_OPEN;

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
	 * \return 0 - success, -1 - error
	 */
	virtual int open();

	/**
	 * Close connector
	 *
	 * \return 0 - success, -1 - error
	 */
	virtual int close();

	/**
	 * Check if connector is open
	 *
	 * \return true - connector is open, false - connector is closed
	 */
	virtual bool isOpen();

	/**
	 * Read data from connector
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from connector, wait for timeout msec
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - buffer size
	 * \param[in] uint32_t timeout - read timeout (msec)
	 *
	 * \return number of read bytes if success, -1 if error or timeout reached
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize, uint32_t timeout);

	/**
	 * Write data to connector
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	virtual int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	bool opened = false;
};

#endif /* COURIERCXX_CONNECTOR_ICONNECTORBASE_H_ */
