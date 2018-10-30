/*
 * I2CPortBase.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_I2C_I2CPORTBASE_H_
#define COURIERCXX_CONNECTOR_I2C_I2CPORTBASE_H_

#include <cstdint>
#include <string>

#include "../IConnectorBase.h"

/**
 * I2C port base class
 */
class I2CPortBase: public IConnectorBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string name - i2c port path
	 * \param[in] uint8_t addr - address on bus
	 */
	I2CPortBase(std::string name, uint8_t addr);

	I2CPortBase(const I2CPortBase& port) = default;
	I2CPortBase(I2CPortBase&& port) = default;

	/**
	 * Destructor
	 */
	virtual ~I2CPortBase();

	I2CPortBase& operator=(const I2CPortBase& port) = default;
	I2CPortBase& operator=(I2CPortBase&& port) = default;

	/**
	 * Open i2c port
	 *
	 * \return 0 - success, -1 - error
	 */
	int open();

	/**
	 * Close i2c port
	 *
	 * \return 0 - success, -1 - error
	 */
	int close();

	/**
	 * Read data from i2c port
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to i2c port
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	std::string name = "";
	uint8_t addr = 0;
	int fd = -1;

};

#endif /* COURIERCXX_CONNECTOR_I2C_I2CPORTBASE_H_ */
