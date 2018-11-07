/*
 * SPIPortBase.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_
#define COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_

#include <cstdint>

#include "../IConnectorBase.h"

class GPIOPortBase;

/**
 * SPI connector class
 */
class SPIPortBase : public IConnectorBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] int16_t mosi - mosi pin
	 * \param[in] int16_t miso - miso pin
	 * \param[in] int16_t clk - clk pin
	 * \param[in] int16_t cs - cs pin
	 */
	SPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs);

	/**
	 * Destructor
	 */
	virtual ~SPIPortBase();

	/**
	 * Open port
	 *
	 * \return 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close port
	 *
	 * \return 0 if success, -1 if error
	 */
	int close();

	/**
	 * Write data to port
	 *
	 * \param[in] const uint8_t buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of bytes written if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from port
	 *
	 * \param[out] uint8_t buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write one byte
	 *
	 * \param[in] uint8_t byte - byte to write
	 *
	 * \return 0 if success, -1 if error
	 */
	int writeByte(uint8_t byte);

private:
	int16_t mosi = -1;
	int16_t miso = -1;
	int16_t clk = -1;
	int16_t cs = -1;

	GPIOPortBase* gpioMOSI = nullptr;
	GPIOPortBase* gpioMISO = nullptr;
	GPIOPortBase* gpioCLK = nullptr;
	GPIOPortBase* gpioCS = nullptr;

	/**
	 * Set MOSI pin state
	 *
	 * \param[in] bool state - state
	 */
	void setMOSIState(bool state);

	/**
	 * Set MISO pin state
	 *
	 * \param[in] bool state - state
	 */
	void setMISOState(bool state);

	/**
	 * Set CS pin state
	 *
	 * \param[in] bool state - state
	 */
	void setCSState(bool state);

	/**
	 * Set CLK pin state
	 *
	 * \param[in] bool state - state
	 */
	void setCLKState(bool state);

	/**
	 * Write single byte
	 *
	 * \param[in] uint8_t byte
	 */
	void write(uint8_t byte);

	void clean();
};

#endif /* COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_ */
