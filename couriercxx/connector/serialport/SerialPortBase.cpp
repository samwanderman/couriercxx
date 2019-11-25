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

#ifdef DEBUG
#include "../../logger/Log.h"
#endif

#define READ_TIMEOUT	50000

SerialPortBase::SerialPortBase(Config config) : IConnectorBase() {
	this->config = config;
}

SerialPortBase::SerialPortBase(std::string path) {
	config.path = path;
}

SerialPortBase::SerialPortBase(std::string path, uint32_t baudrate) : SerialPortBase(path) {
	config.baudrate = baudrate;
}

SerialPortBase::SerialPortBase(std::string path, uint32_t baudrate, uint32_t timeout) : SerialPortBase(path, baudrate) {
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
		return ERR_ALREADY_OPEN;
	}

	fd = ::open(config.path.c_str(), O_RDWR | O_NOCTTY);
	if (fd == -1) {
		return ERR_DEFAULT;
	}

	if (setBaudrate(config.baudrate) == -1) {
		clean();

		return ERR_DEFAULT;
	}

	if (config.nonBlock) {
		int flags = fcntl(fd, F_GETFL, 0);
		if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
			clean();

			return ERR_DEFAULT;
		}
	}

	return IConnectorBase::open();
}

int SerialPortBase::close() {
	if (!isOpen()) {
		return ERR_NOT_OPEN;
	}

	clean();

	return IConnectorBase::close();
}

void SerialPortBase::clean() {
	::close(fd);
}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return read(buffer, bufferSize, -1);
}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize, int32_t timeout) {
	if (!isOpen()) {
		return ERR_DEFAULT;
	}

	if (timeout == -1) {
		timeout = config.timeout;
	}

	if (config.nonBlock) {
		int bytesRead = 0;

//		uint64_t lastOperationTime = Clock::getTimestamp();
//
//		while ((lastOperationTime + timeout > Clock::getTimestamp()) && ((uint32_t) bytesRead <= bufferSize)) {
//			int res = ::read(fd, &buffer[bytesRead], bufferSize - bytesRead);
//			if (res != -1) {
//				bytesRead += res;
//				lastOperationTime = Clock::getTimestamp();
//			}
//		}

		// operation hard timeout
		uint64_t endTimeout = Clock::getTimestampExt() + timeout * 1000;
		uint64_t lastOperationTime = 0;

		while (true) {
			// get current time in microsecs
			uint64_t currentTime = Clock::getTimestampExt();

			// check end timeout exceed
			if (currentTime >= endTimeout) {
				break;
			}

			// check byte buffer exceed
			if ((uint32_t) bytesRead >= bufferSize) {
				break;
			}

			// Check if last read operation was too long ago
			if ((lastOperationTime != 0) && (currentTime - lastOperationTime > READ_TIMEOUT)) {
				break;
			}

			int res = ::read(fd, &buffer[bytesRead], bufferSize - bytesRead);

#ifdef DEBUG
			if (res > 0) {
				Log::log("< ");
				for (int i = 0; i < res; i++) {
					Log::log("%02x ", buffer[bytesRead + i]);
				}
				Log::log("\r\n");
			}
#endif

			if (res != -1) {
				bytesRead += res;
				lastOperationTime = Clock::getTimestampExt();
			}
		}

		return bytesRead;
	} else {
		if (timeout > 0) {
			fd_set set;
			struct timeval timeoutVal;

			FD_ZERO(&set);
			FD_SET(fd, &set);

			uint64_t t = timeout * 1000;
			timeoutVal.tv_sec = t / 1000000;
			timeoutVal.tv_usec = t % 1000000;

			int rv = select(fd + 1, &set, nullptr, nullptr, &timeoutVal);
			if (rv == -1) {
				return ERR_DEFAULT;
			} else if (rv == 0) {
				return ERR_TIMEOUT;
			}
		}

		int res = ::read(fd, buffer, bufferSize);

#ifdef DEBUG
		if (res > 0) {
			Log::log("< ");
			for (int i = 0; i < res; i++) {
				Log::log("%02x ", buffer[i]);
			}
			Log::log("\r\n");
		}
#endif

		return res;
	}
}

int SerialPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return ERR_DEFAULT;
	}

	int res = ::write(fd, buffer, bufferSize);

#ifdef DEBUG
	if (res > 0) {
		Log::log("> ");
		for (int i = 0; i < (int) bufferSize; i++) {
			Log::log("%02x ", buffer[i]);
		}
		Log::log("\r\n");
	}
#endif

	return res;
}

int SerialPortBase::setBaudrate(uint32_t baudrate) {
	config.baudrate = baudrate;
	uint32_t convertedBaudrate = 0;
	switch (baudrate) {
	case 9600:
		convertedBaudrate = B9600;

		break;

	case 19200:
		convertedBaudrate = B19200;

		break;

	case 38400:
		convertedBaudrate = B38400;

		break;

	case 57600:
		convertedBaudrate = B57600;

		break;

	case 115200:
		convertedBaudrate = B115200;

		break;
	}

	struct termios tty;
	memset(&tty, 0, sizeof(tty));

	if (tcgetattr(fd, &tty) != 0) {
		clean();

		return ERR_DEFAULT;
	}

	if (convertedBaudrate != 0) {
		if (cfsetospeed(&tty, convertedBaudrate) == -1) {
			return ERR_DEFAULT;
		}

		if (cfsetispeed(&tty, convertedBaudrate) == -1) {
			return ERR_DEFAULT;
		}
	}

	uint8_t dateBits = 0;
	switch (config.dateBits) {
	case 5:
		dateBits = CS5;

		break;

	case 6:
		dateBits = CS6;

		break;

	case 7:
		dateBits = CS7;

		break;

	case 8:
	default:
		dateBits = CS8;

		break;
	}

	tty.c_cflag &= config.parityCheck ? PARENB : ~PARENB;
	tty.c_cflag &= config.stopBit ? CSTOPB : ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= dateBits;
	tty.c_cflag &= ~CRTSCTS;
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 5;
	tty.c_cflag |= CREAD | CLOCAL;

	cfmakeraw(&tty);

	if (tcflush(fd, TCIFLUSH) == -1) {
		clean();

		return ERR_DEFAULT;
	}

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		clean();

		return ERR_DEFAULT;
	}

	return 0;
}

uint32_t SerialPortBase::getBaudrate() {
	return config.baudrate;
}
