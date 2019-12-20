/*
 * SPIPortBase.h
 *
 *  Created on: 21.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_
#define COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_

#include <cstdint>
#include <string>

#ifdef _WIN32
#else
#include <linux/spi/spidev.h>
#endif

#include "../IConnectorBase.h"

struct spi_ioc_transfer;

class SPIPortBase  : public IConnectorBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string path - path
	 */
	SPIPortBase(std::string path);

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
	int fd = -1;
#ifdef _WIN32
#else
	struct spi_ioc_transfer spi;
#endif
	uint32_t speed = 0;
	uint8_t bits = 0;
	std::string path = "";
};

#endif /* COURIERCXX_CONNECTOR_SPI_SPIPORTBASE_H_ */
