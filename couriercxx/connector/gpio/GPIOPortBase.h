/*
 * GPIOPortBase.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_GPIO_GPIOPORTBASE_H_
#define COURIERCXX_CONNECTOR_GPIO_GPIOPORTBASE_H_

#include <cstdint>

#include "../IConnectorBase.h"

/**
 * GPIO port base class
 */
class GPIOPortBase : public IConnectorBase {
public:
	/**
	 * Direction type
	 */
	enum Direction {
		NONE = 0,
		IN,
		OUT
	};
	typedef enum Direction Direction;

	/**
	 * Pin value
	 */
	enum Value {
		ZERO = 0x30,
		ONE = 0x31
	};
	typedef enum Value Value;

	/**
	 * Construtor
	 *
	 * \param[in] uint8_t pid - pin id
	 */
	GPIOPortBase(uint8_t pid);

	/**
	 * Constructor
	 *
	 * \param[in] uint8_t pid - pin id
	 * \param[in] Direction direction - direction
	 */
	GPIOPortBase(uint8_t pid, Direction direction);

	GPIOPortBase(const GPIOPortBase& port) = default;
	GPIOPortBase(GPIOPortBase&& port) = default;

	/**
	 * Destructor
	 */
	virtual ~GPIOPortBase();

	GPIOPortBase& operator=(const GPIOPortBase& port) = default;
	GPIOPortBase& operator=(GPIOPortBase&& port) = default;

	/**
	 * Open gpio port
	 *
	 * \return 0 - success, -1 - error
	 */
	int open();

	/**
	 * Close gpio port
	 *
	 * \return 0 - success, -1 - error
	 */
	int close();

	/**
	 * Read data from gpio port
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to pgio port
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Export gpio port
	 *
	 * \return 0 - success, -1 - error
	 */
	int exportGPIO();

	/**
	 * Unexport gpio port
	 *
	 * \return 0 - success, -1 - error
	 */
	int unexportGPIO();

	/**
	 * Set direction to port
	 *
	 * \return 0 - success, -1 - error
	 */
	int setDirection(Direction direction);

	/**
	 * Get port direction
	 *
	 * \return direction
	 */
	Direction getDirection();

	/**
	 * Write value to port
	 *
	 * \return 0 - success, -1 - error
	 */
	int setValue(uint8_t value);

	/**
	 * Read value from port
	 *
	 * \return value > 0 from port if success, -1 - if error
	 */
	int getValue();

	/**
	 * Get port pin id
	 *
	 * \return pin id
	 */
	uint8_t getPID();

private:
	uint8_t pid = 0;
	Direction direction = NONE;

	void clean();
};

#endif /* COURIERCXX_CONNECTOR_GPIO_GPIOPORTBASE_H_ */
