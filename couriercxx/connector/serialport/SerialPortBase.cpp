/*
 * SerialPortBase.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBase.h"

#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

#include "../../util/Clock.h"

SerialPortBase::SerialPortBase(Config config) : IConnectorBase() {
	this->config = config;
}

SerialPortBase::SerialPortBase(std::string name) {
	config.name = name;
}

SerialPortBase::SerialPortBase(std::string name, uint32_t baudrate) : SerialPortBase(name) {
	config.baudrate = baudrate;
}

SerialPortBase::SerialPortBase(std::string name, uint32_t baudrate, uint32_t timeout) : SerialPortBase(name, baudrate) {
	config.timeout = timeout;
}

SerialPortBase::SerialPortBase(SerialPortBase&& other) : IConnectorBase(other) {
	this->config = other.config;
	memset(&other.config, 0, sizeof(other.config));
	this->fd = other.fd;
	other.fd = -1;
}

SerialPortBase::~SerialPortBase() { }

SerialPortBase& SerialPortBase::operator=(SerialPortBase&& other) {
	IConnectorBase::operator=(other);
	this->config = other.config;
	memset(&other.config, 0, sizeof(other.config));
	this->fd = other.fd;
	other.fd = -1;

	return *this;
}

int SerialPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	fd = ::open(config.name.c_str(), O_RDWR | O_NOCTTY);
	if (fd == -1) {
		return -1;
	}

	if (setBaudrate(config.baudrate) == -1) {
		clean();

		return -1;
	}

	if (config.nonBlock) {
		int flags = fcntl(fd, F_GETFL, 0);
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
			clean();

			return -1;
		}
	}

	return IConnectorBase::open();
}

int SerialPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	clean();

	return IConnectorBase::close();
}

void SerialPortBase::clean() {
	::close(fd);
}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	if (config.nonBlock) {
		int bytesRead = 0;

		uint64_t lastOperationTime = Clock::getTimestamp();

		while ((lastOperationTime + config.timeout > Clock::getTimestamp()) && ((uint32_t) bytesRead < bufferSize)) {
			int res = ::read(fd, &buffer[bytesRead], bufferSize - bytesRead);
			if (res != -1) {
				bytesRead += res;
				lastOperationTime = Clock::getTimestamp();
			}
		}

		return bytesRead;
	} else {
		if (config.timeout > 0) {
			fd_set set;
			struct timeval timeoutVal;

			FD_ZERO(&set);
			FD_SET(fd, &set);

			timeoutVal.tv_sec = 0;
			timeoutVal.tv_usec = config.timeout;

			int rv = select(fd + 1, &set, NULL, NULL, &timeoutVal);
			if (rv == -1) {
				return -1;
			} else if (rv == 0) {
				return -1;
			}
		}

		return ::read(fd, buffer, bufferSize);
	}
}

int SerialPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::write(fd, buffer, bufferSize);
}

int SerialPortBase::setBaudrate(uint32_t baudrate) {
	config.baudrate = baudrate;
	uint32_t convertedSpeed = 0;
	switch (baudrate) {
	case 9600:
		convertedSpeed = B9600;

		break;

	case 19200:
		convertedSpeed = B19200;

		break;

	case 38400:
		convertedSpeed = B38400;

		break;

	case 57600:
		convertedSpeed = B57600;

		break;

	case 115200:
		convertedSpeed = B115200;

		break;
	}

	struct termios tty;
	memset(&tty, 0, sizeof(tty));

	if (tcgetattr(fd, &tty) != 0) {
		clean();

		return -1;
	}

	if (convertedSpeed != 0) {
		if (cfsetospeed(&tty, convertedSpeed) == -1) {
			return -1;
		}

		if (cfsetispeed(&tty, convertedSpeed) == -1) {
			return -1;
		}
	}

	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;
	tty.c_cflag &= ~CRTSCTS;
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 5;
	tty.c_cflag |= CREAD | CLOCAL;

	cfmakeraw(&tty);

	if (tcflush(fd, TCIFLUSH) == -1) {
		clean();

		return -1;
	}

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		clean();

		return -1;
	}

	return 0;
}

uint32_t SerialPortBase::getBaudrate() {
	return config.baudrate;
}
