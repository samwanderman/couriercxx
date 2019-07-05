#include <cstdint>

#include "../couriercxx/connector/serialport/SerialPortBase.h"
#include "../couriercxx/logger/Log.h"

class SerialPortBase;

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	SerialPortBase::Config config;
	config.name = "/dev/ttyUSB0";
	config.baudrate = 38400;
	config.timeout = 500;
	SerialPortBase port(config);
	if (port.open() == -1) {
		Log::error("SerialPortBase.open() error");

		return -1;
	}
	Log::info("SerialPortBase.open() success");

	uint8_t symbol;
	int res = -1;
	if ((res = port.read(&symbol, 1)) == -1) {
		Log::error("SerialPortBase.read() error");
	} else {
		Log::info("SerialPortBase.read() %i bytes", res);
	}

	if (port.close() == -1) {
		Log::error("SerialPortBase.close() error");
	} else {
		Log::info("SerialPortBase.close() success");
	}

	return 0;
}
