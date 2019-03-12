/**
 * PortTest.cpp
 *
 *  Created on: 23.01.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <cstdint>
#include <cstring>

#include "../couriercxx/connector/serialport/SerialPortBase.h"
#include "../couriercxx/logger/Log.h"

int testPort(const char* portName) {
	Log::debug("Test port %s", portName);

	SerialPortBase* port = new SerialPortBase(portName, 57600, 10000);
	if (port->open() == -1) {
		Log::error("SerialPortBase.open() error");

		delete port;

		return -1;
	}
	Log::debug("SerialPort.open() success");

	const uint8_t testWrite[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 0 };

	int res = -1;
	if ((res = port->write(testWrite, 17)) == -1) {
		Log::error("SerialPortBase.write('%s', %i) error", testWrite, 17);

		port->close();

		delete port;

		return -1;
	}
	Log::debug("SerialPortBase.write('%s', %i) success", testWrite, 17);

	uint8_t testRead[17];
	memset(testRead, 0, 17 * sizeof(uint8_t));
	if ((res = port->read(testRead, 17)) == -1) {
		Log::error("SerialPortBase.read('%s', %i) error", testRead, res);

		port->close();

		delete port;

		return -1;
	}
	Log::debug("SerialPortBase.read('%s', %i) success", testRead, res);

	if (res != 17) {
		port->close();

		delete port;

		return -1;
	}

	for (int i = 0; i < 17; i++) {
		if (testWrite[i] != testRead[i]) {
			port->close();

			delete port;

			return -1;
		}
	}

	if (port->close() == -1) {
		Log::error("SerialPortBase.close() error");

		delete port;

		return -1;
	}
	Log::debug("SerialPortBase.close() success");

	delete port;

	return 0;
}

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);
	Log::info("Start program");

	const char** ports = nullptr;
	uint8_t portsNum = ac - 1;

	if (portsNum == 0) {
		portsNum = 4;
		ports = new const char*[portsNum];
		ports[0] = "/dev/ttyS1";
		ports[1] = "/dev/ttyS2";
		ports[2] = "/dev/ttyUSB0";
		ports[3] = "/dev/ttyUSB1";
	} else {
		ports = new const char*[portsNum];
		for (int i = 0; i < portsNum; i++) {
			ports[i] = av[1 + i];
		}
	}

	for (int i = 0; i < portsNum; i++) {
		if (testPort(ports[i]) == 0) {
			Log::info("TEST %s SUCCESS", ports[i]);
		} else {
			Log::error("TEST %s ERROR", ports[i]);
		}
	}

	delete[] ports;

	return 0;
}
