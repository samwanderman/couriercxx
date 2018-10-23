#include "../couriercxx/connector/serialport/SerialPortBase.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	SerialPortBase port("/dev/ttyUSB0", 9600);

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
