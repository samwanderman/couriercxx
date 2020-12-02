/*
 * GPIOSPIPortBase.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SPI_GPIOSPIPORTBASE_H_
#define COURIERCXX_CONNECTOR_SPI_GPIOSPIPORTBASE_H_

#include <cstdint>
#include <mutex>
#include <thread>

#include "../IConnectorBase.h"
#include "../../Types.h"

class GPIOPortBase;

#define SPI_BUFFER_SIZE	1024

/**
 * SPI connector class
 */
class GPIOSPIPortBase : public IConnectorBase {
public:
	static const uint16_t MODE0;
	static const uint16_t MODE1;
	static const uint16_t MODE2;
	static const uint16_t MODE3;

	/**
	 * Constructor
	 *
	 * \param[in] int16_t mosi - mosi pin
	 * \param[in] int16_t miso - miso pin
	 * \param[in] int16_t clk - clk pin
	 * \param[in] int16_t cs - cs pin
	 * \param[in] uint16_t mode - mode
	 */
	GPIOSPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs, uint16_t mode);

	/**
	 * Constructor
	 *
	 * \param[in] int16_t mosi - mosi pin
	 * \param[in] int16_t miso - miso pin
	 * \param[in] int16_t clk - clk pin
	 * \param[in] int16_t cs - cs pin
	 */
	GPIOSPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs);

	/**
	 * Destructor
	 */
	virtual ~GPIOSPIPortBase();

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
	 * Read buffer
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer max size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write buffer
	 *
	 * \param[in] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer max size
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	uint16_t mosi = -1;
	uint16_t miso = -1;
	uint16_t clk = -1;
	uint16_t cs = -1;

	GPIOPortBase* gpioMOSI = nullptr;
	GPIOPortBase* gpioMISO = nullptr;
	GPIOPortBase* gpioCLK = nullptr;
	GPIOPortBase* gpioCS = nullptr;

	// SPI mode
	uint8_t mode = MODE2;

	bool running = false;

	uint8_t inputBuffer[SPI_BUFFER_SIZE];
	uint32_t inputBufferLen = 0;
	std::mutex inputBufferMutex;

	uint8_t outputBuffer[SPI_BUFFER_SIZE];
	uint32_t outputBufferLen = 0;
	std::mutex outputBufferMutex;

	std::thread th;

	void clean();

	void setMOSI();
	void clearMOSI();
	void setCLK();
	void clearCLK();
	void setCS();
	void clearCS();
	uint8_t readMISO();
	void delay(Timeout timeout);
};

#endif /* COURIERCXX_CONNECTOR_SPI_GPIOSPIPORTBASE_H_ */
