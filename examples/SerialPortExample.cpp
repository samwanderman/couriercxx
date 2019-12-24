/**
 * Blocking serial port example
 */

#include "../couriercxx/connector/serialport/SerialPortBase.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 3) {
		Log::info("\r\nUsage:\r\n%s port_name port_baudrate", &av[0][2]);

		return 0;
	}

	SerialPortBase port(av[1], atoi(av[2]));

	if (port.open() == -1) {
		Log::error("SerialPortBase.open() error");

		return -1;
	}
	Log::info("SerialPortBase.close() success");

	if (port.close() == -1) {
		Log::error("SerialPortBase.close() error");
	} else {
		Log::info("SerialPortBase.close() success");
	}

	return 0;
}
