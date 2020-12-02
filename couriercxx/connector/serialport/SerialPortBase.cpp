/*
 * SerialPortBase.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBase.h"

#include <fcntl.h>
#include <cinttypes>

#ifndef _WIN32

#include <sys/select.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

#endif

#include <cstring>

#include "../../util/Clock.h"
#include "../../logger/Log.h"

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

SerialPortBase::SerialPortBase(std::string path, uint32_t baudrate, Timeout timeout) : SerialPortBase(path, baudrate) {
	config.timeout = timeout;
}

SerialPortBase::SerialPortBase(SerialPortBase&& other) : IConnectorBase(other) {
	this->config = other.config;
	this->fd = other.fd;

#ifdef _WIN32

	other.fd = nullptr;

#else

	other.fd = -1;

#endif
}

SerialPortBase::~SerialPortBase() { }

SerialPortBase& SerialPortBase::operator=(SerialPortBase&& other) {
	IConnectorBase::operator=(other);
	this->config = other.config;
	this->fd = other.fd;

#ifdef _WIN32

	other.fd = nullptr;

#else

	other.fd = -1;

#endif

	return *this;
}

int SerialPortBase::open() {
	if (isOpen()) {
		return ERR_ALREADY_OPEN;
	}

#ifdef _WIN32

	Log::debug("SerialPort.open('%s', %u)", config.path.c_str(), config.baudrate);

	std::string path = std::string(config.path.c_str());
	if (path.size() > 4) {
		path = "\\\\.\\" + path;
	}

	fd = ::CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (fd == INVALID_HANDLE_VALUE) {
		return ERR_DEFAULT;
	}

	if (setBaudrate(config.baudrate) == -1) {
		clean();

		return ERR_DEFAULT;
	}

#else

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

#endif

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

#ifdef _WIN32

	::CloseHandle(fd);

#else

	::close(fd);

#endif

}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
//	Log::debug("SerialPort.read()");

	return read(buffer, bufferSize, -1);
}

int SerialPortBase::read(uint8_t* buffer, uint32_t bufferSize, Timeout timeout) {
//	Log::debug("SerialPort.read(%i)", timeout);

	if (!isOpen()) {
		return ERR_DEFAULT;
	}

	int res = -1;

#ifdef _WIN32

	DWORD readBytes = -1;

	if (!::ReadFile(fd, (LPVOID) buffer, (DWORD) bufferSize, &readBytes, nullptr)) {
		return -1;
	}

	res = (int) readBytes;

#else

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
		Timeout endTimeout = Clock::getTimestampExt() + timeout * 1000;
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
			struct timespec timeoutVal;

			FD_ZERO(&set);
			FD_SET(fd, &set);

			timeoutVal.tv_sec = timeout / 1000;
			timeoutVal.tv_nsec = (timeout % 1000) * 1000000;

			int rv = pselect(fd + 1, &set, nullptr, nullptr, &timeoutVal, nullptr);
			if (rv == -1) {
				return ERR_DEFAULT;
			} else if (rv == 0) {
				return ERR_TIMEOUT;
			}
		}

		res = ::read(fd, buffer, bufferSize);
	}

#endif

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

int SerialPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
//	Log::debug("SerialPortBase.write()");

	if (!isOpen()) {
		return ERR_DEFAULT;
	}

	int res = -1;

#ifdef _WIN32

	DWORD bytesWritten = -1;

	if (!::WriteFile(fd, (LPCVOID) buffer, (DWORD) bufferSize, &bytesWritten, nullptr)) {
		return -1;
	}

	res = (int) bytesWritten;

#else

	res = ::write(fd, buffer, bufferSize);

#endif

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
//	Log::debug("SerialPortBase.setBaudrate(%u)", baudrate);

	config.baudrate = baudrate;

#ifdef _WIN32

	DCB dcbSerialParams = {0};
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(fd, &dcbSerialParams)) {
		return -1;
	}

//#ifdef DEBUG
//
//	Log::debug("Length is %u",				dcbSerialParams.DCBlength);
//	Log::debug("BaudRate is %u",			dcbSerialParams.BaudRate);
//	Log::debug("fBinary is %u",				dcbSerialParams.fBinary);
//	Log::debug("fParity is %u",				dcbSerialParams.fParity);
//	Log::debug("fOutxCtsFlow is %u",		dcbSerialParams.fOutxCtsFlow);
//	Log::debug("fOutxDsrFlow is %u",		dcbSerialParams.fOutxDsrFlow);
//	Log::debug("fDtrControl is %u",			dcbSerialParams.fDtrControl);
//	Log::debug("fDsrSensitivity is %u",		dcbSerialParams.fDsrSensitivity);
//	Log::debug("fTXContinueOnXoff is %u",	dcbSerialParams.fTXContinueOnXoff);
//	Log::debug("fOutX is %u",				dcbSerialParams.fOutX);
//	Log::debug("fInX is %u",				dcbSerialParams.fInX);
//	Log::debug("fErrorChar is %u",			dcbSerialParams.fErrorChar);
//	Log::debug("fNull is %u",				dcbSerialParams.fNull);
//	Log::debug("fRtsControl is %u",			dcbSerialParams.fRtsControl);
//	Log::debug("fAbortOnError is %u",		dcbSerialParams.fAbortOnError);
//	Log::debug("XonLim is %u",				dcbSerialParams.XonLim);
//	Log::debug("XoffLim is %u",				dcbSerialParams.XoffLim);
//	Log::debug("ByteSize is %u",			dcbSerialParams.ByteSize);
//	Log::debug("Parity is %u",				dcbSerialParams.Parity);
//	Log::debug("StopBits is %u",			dcbSerialParams.StopBits);
//	Log::debug("XonChar is %u",				dcbSerialParams.XonChar);
//	Log::debug("XoffChar is %u",			dcbSerialParams.XoffChar);
//	Log::debug("ErrorChar is %u",			dcbSerialParams.ErrorChar);
//	Log::debug("EofChar is %u",				dcbSerialParams.EofChar);
//	Log::debug("EvtChar is %u",				dcbSerialParams.EvtChar);
//
//#endif

	uint32_t convertedBaudrate = 0;
	switch (baudrate) {
	case 9600:
		convertedBaudrate = CBR_9600;

		break;

	case 19200:
		convertedBaudrate = CBR_19200;

		break;

	case 38400:
		convertedBaudrate = CBR_38400;

		break;

	case 57600:
		convertedBaudrate = CBR_57600;

		break;

	case 115200:
		convertedBaudrate = CBR_115200;

		break;
	}

	dcbSerialParams.BaudRate		= convertedBaudrate;
	dcbSerialParams.ByteSize		= config.dataBits;
	dcbSerialParams.Parity			= config.parityCheck ? ODDPARITY : NOPARITY;
	dcbSerialParams.StopBits		= config.stopBit ? TWOSTOPBITS : ONESTOPBIT;

	COMMTIMEOUTS timeouts;
	GetCommTimeouts(fd, &timeouts);

#ifdef DEBUG

	Log::debug("ReadIntervalTimeout         %u", timeouts.ReadIntervalTimeout);
	Log::debug("ReadTotalTimeoutConstant    %u", timeouts.ReadTotalTimeoutConstant);
	Log::debug("ReadTotalTimeoutMultiplier  %u", timeouts.ReadTotalTimeoutMultiplier);
	Log::debug("WriteTotalTimeoutConstant   %u", timeouts.WriteTotalTimeoutConstant);
	Log::debug("WriteTotalTimeoutMultiplier %u", timeouts.WriteTotalTimeoutMultiplier);

#endif

	timeouts.ReadIntervalTimeout			= 0xffffffff;
	timeouts.ReadTotalTimeoutMultiplier		= 0;

	if (config.timeout > 0) {
		timeouts.ReadIntervalTimeout = config.timeout;
	}

	if (!SetCommTimeouts(fd, &timeouts)) {
		Log::error("SetCommTimeouts() error");
	}

	if(!SetCommState(fd, &dcbSerialParams)) {
		return -1;
	}

#else
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

	uint8_t dataBits = 0;
	switch (config.dataBits) {
	case 5:
		dataBits = CS5;

		break;

	case 6:
		dataBits = CS6;

		break;

	case 7:
		dataBits = CS7;

		break;

	case 8:
	default:
		dataBits = CS8;

		break;
	}

	tty.c_cflag &= config.parityCheck ? PARENB : ~PARENB;
	tty.c_cflag &= config.stopBit ? CSTOPB : ~CSTOPB;
	tty.c_cflag &= config.handshake ? CRTSCTS : ~CRTSCTS;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= dataBits;
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

#endif

	return 0;
}

uint32_t SerialPortBase::getBaudrate() {
	return config.baudrate;
}

bool SerialPortBase::isValid() {
#ifdef _WIN32
	return true;
#else
	return (fcntl(fd, F_GETFL) != -1) || (errno != EBADF);
#endif
}

void SerialPortBase::clear() {

#ifndef _WIN32

	tcflush(fd, TCIOFLUSH);

#endif

}
