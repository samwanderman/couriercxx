/*
 * SPIPortBase2.cpp
 *
 *  Created on: 21.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include "SPIPortBase.h"

SPIPortBase::SPIPortBase(std::string path) {
	this->path = path;
}

SPIPortBase::~SPIPortBase() { }

int SPIPortBase::open() {
	fd = ::open(path.c_str(), O_RDWR);
	if (fd == -1) {
		return -1;
	}

	const uint8_t mode = 2;

	int res = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (res == -1) {
		close();

		return -1;
	}

	res = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (res == -1) {
		close();

		return -1;
	}

	uint8_t lsb = 0;
	res = ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb);
	if (res == -1) {
		close();

		return -1;
	}

	uint8_t bits = 8;
	res = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (res == -1) {
		close();

		return -1;
	}

	res = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &this->bits);
	if (res == -1) {
		close();

		return -1;
	}

	uint16_t speed = 16000;
	res = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (res == -1) {
		close();

		return -1;
	}

	res = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed);
	if (res == -1) {
		close();

		return -1;
	}

	return 0;
}

int SPIPortBase::close() {
	if (fd != -1) {
		::close(fd);
		fd = -1;
	}

	return 0;
}

int SPIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}

int SPIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	uint8_t rx[bufferSize];
	memset(rx, 0, bufferSize * sizeof(uint8_t));

	memset(&spi, 0, sizeof(spi));
	spi.tx_buf = (uint64_t) buffer;
	spi.rx_buf = (uint64_t) rx;
	spi.len = bufferSize;
	spi.delay_usecs = 0;
	spi.speed_hz = speed;
	spi.bits_per_word = bits;
	spi.cs_change = 0;

	int res = ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
	switch (res) {
	case EBADF:
		return -1;

	case EFAULT:
		return -1;

	case EINVAL:
		return -1;

	case ENOTTY:
		return -1;

	default:
		if (res < 0) {
			return -1;
		}
	}

	return bufferSize;
}
