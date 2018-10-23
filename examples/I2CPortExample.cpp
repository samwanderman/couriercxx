#include "../couriercxx/connector/i2c/I2CPortBase.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	I2CPortBase port("/dev/i2c-0", 0x08);

	if (port.open() == -1) {
		Log::error("I2CPortBase.open() error");

		return -1;
	}
	Log::debug("I2CPortBase.open() success");

	if (port.close() == -1) {
		Log::error("I2CPortBase.close() error");

		return -1;
	}
	Log::debug("I2CPortBase.close() success");

	return 0;
}
