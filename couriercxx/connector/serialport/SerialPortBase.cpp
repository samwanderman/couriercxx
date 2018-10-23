/*
 * SerialPortBase.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../../../couriercxx/connector/serialport/SerialPortBase.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

SerialPortBase::SerialPortBase(std::string name) : SerialPortBase(name, 0) { }

SerialPortBase::SerialPortBase(std::string name, uint32_t speed) : IConnectorBase() {
	this->name = name;

	switch (speed) {
	case 9600:
		this->speed = B9600;

		break;

	case 38400:
		this->speed = B38400;

		break;

	case 57600:
		this->speed = B57600;

		break;

	default:
		this->speed = speed;
	}
}

SerialPortBase::~SerialPortBase() { }

int SerialPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	fd = ::open(name.c_str(), O_RDWR | O_NOCTTY);
	if (fd == -1) {
		return -1;
	}

	struct termios tty;
	memset(&tty, 0, sizeof(tty));

	if (tcgetattr(fd, &tty) != 0) {
		close();

		return -1;
	}

	if (speed != 0) {
		if (cfsetospeed(&tty, speed) == -1) {
			close();

			return -1;
		}

		if (cfsetispeed(&tty, speed) == -1) {
			close();

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
		close();

		return -1;
	}

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		close();

		return -1;
	}

	return IConnectorBase::open();
}

int SerialPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	int res = 0;

	if (fd != -1) {
		res = ::close(fd);
		fd = -1;
	} else {
		res = -1;
	}

	if (IConnectorBase::close() == -1) {
		return -1;
	}

	return res;
}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::read(fd, buffer, bufferSize);
}

int SerialPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::write(fd, buffer, bufferSize);
}
