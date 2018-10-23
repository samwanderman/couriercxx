#include "../couriercxx/connector/gpio/GPIOPortBase.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	GPIOPortBase gpio(6);

	if (gpio.exportGPIO() == -1) {
		Log::error("GPIOPortBase.export() error");

		return -1;
	}
	Log::debug("GPIOPortBase.export() success");

	if (gpio.setDirection(GPIOPortBase::Direction::OUT) == -1) {
		Log::error("GPIOPortBase.setDirection() error");

		gpio.unexportGPIO();

		return -1;
	}
	Log::debug("GPIOPortBase.setDirection() success");

	if (gpio.setValue(1) == -1) {
		Log::error("GPIOPortBase.setValue() error");

		gpio.unexportGPIO();

		return -1;
	}
	Log::debug("GPIOPortBase.setValue() success");

	if (gpio.getValue() == -1) {
		Log::error("GPIOPortBase.getValue() error");

		gpio.unexportGPIO();

		return -1;
	}
	Log::debug("GPIOPortBase.getValue() success");

	if (gpio.unexportGPIO() == -1) {
		Log::error("GPIOPortBase.unexportGPIO() error");

		return -1;
	}
	Log::debug("GPIOPortBase.unexportGPIO() success");

	return 0;
}
