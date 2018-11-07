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
	/**
	 * Empty construtor
	 */
	IConnectorBase();
	IConnectorBase(const IConnectorBase& connector) = default;
	IConnectorBase(IConnectorBase&& connector) = default;
	/**
	 * Destructor
	 */
	virtual ~IConnectorBase();
	IConnectorBase& operator=(const IConnectorBase& connector) = default;
	IConnectorBase& operator=(IConnectorBase&& connector) = default;

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
	virtual bool isOpen() const;

	/**
	 * Read data from connector
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	virtual int read(uint8_t* buffer, uint32_t bufferSize) = 0;

	/**
	 * Write data to connector
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	virtual int write(const uint8_t* buffer, uint32_t bufferSize) = 0;

private:
	bool opened = false;
};

#endif /* COURIERCXX_CONNECTOR_ICONNECTORBASE_H_ */
