/*
 * SPIPortBaseBase.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SPIPortBase.h"

#include "../gpio/GPIOPortBase.h"

SPIPortBase::SPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs) : IConnectorBase() {
	this->mosi = mosi;
	this->miso = miso;
	this->clk = clk;
	this->cs = cs;
}

SPIPortBase::~SPIPortBase() {
	close();
}

int SPIPortBase::open() {
	if (IConnectorBase::open() == -1) {
		return -1;
	}

	gpioMOSI = new GPIOPortBase(mosi);

	if (gpioMOSI->open() == -1) {
		close();

		return -1;
	}

	gpioMOSI->unexportGPIO();
	if (gpioMOSI->exportGPIO() == -1) {
		close();

		return -1;
	}

	if (gpioMOSI->setDirection(GPIOPortBase::Direction::OUT) == -1) {
		close();

		return -1;
	}

	gpioMISO = new GPIOPortBase(miso);
	if (gpioMISO->open() == -1) {
		close();

		return -1;
	}
	gpioMISO->unexportGPIO();
	if (gpioMISO->exportGPIO() == -1) {
		close();

		return -1;
	}

	if (gpioMISO->setDirection(GPIOPortBase::Direction::OUT) == -1) {
		close();

		return -1;
	}

	gpioCLK = new GPIOPortBase(clk);
	if (gpioCLK->open() == -1) {
		close();

		return -1;
	}
	gpioCLK->unexportGPIO();
	if (gpioCLK->exportGPIO() == -1) {
		close();

		return -1;
	}

	if (gpioCLK->setDirection(GPIOPortBase::Direction::OUT) == -1) {
		close();

		return -1;
	}

	gpioCS = new GPIOPortBase(cs);
	if (gpioCS->open() == -1) {
		close();

		return -1;
	}
	gpioCS->unexportGPIO();
	if (gpioCS->exportGPIO() == -1) {
		close();

		return -1;
	}

	if (gpioCS->setDirection(GPIOPortBase::Direction::OUT) == -1) {
		close();

		return -1;
	}

	return 0;
}

int SPIPortBase::close() {
	if (IConnectorBase::close() == -1) {
		return -1;
	}

	if (gpioMOSI != nullptr) {
		gpioMOSI->unexportGPIO();
		delete gpioMOSI;
		gpioMOSI = nullptr;
	}

	if (gpioMISO != nullptr) {
		gpioMISO->unexportGPIO();
		delete gpioMISO;
		gpioMISO = nullptr;
	}

	if (gpioCLK != nullptr) {
		gpioCLK->unexportGPIO();
		delete gpioCLK;
		gpioCLK = nullptr;
	}

	if (gpioCS != nullptr) {
		gpioCS->unexportGPIO();
		delete gpioCS;
		gpioCS = nullptr;
	}

	return 0;
}


int SPIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	setCSState(false);

	for (uint32_t i = 0; i < bufferSize; i++) {
		write(buffer[i]);
	}

	setCSState(true);

	return 0;
}

int SPIPortBase::writeByte(uint8_t byte) {
	if (!isOpen()) {
		return -1;
	}

	setCSState(false);
	write(byte);
	setCSState(true);

	return 0;
}

int SPIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return 0;
}

void SPIPortBase::setMOSIState(bool state) {
	if (gpioMOSI != nullptr) {
		gpioMOSI->setValue(state ? 1 : 0);
	}
}

void SPIPortBase::setMISOState(bool state) {
	if (gpioMISO != nullptr) {
		gpioMISO->setValue(state ? 1 : 0);
	}
}

void SPIPortBase::setCSState(bool state) {
	if (gpioCS != nullptr) {
		gpioCS->setValue(state ? 1 : 0);
	}

}

void SPIPortBase::setCLKState(bool state) {
	if (gpioCLK != nullptr) {
		gpioCLK->setValue(state ? 1 : 0);
	}
}

void SPIPortBase::write(uint8_t byte) {
	if (!isOpen()) {
		return;
	}

	for (uint8_t bit = 0; bit < 8 ; bit++) {
		if ((byte & 0x80) > 0) {
			setMOSIState(true);
		} else {
			setMOSIState(false);
		}
		byte <<= 1;

		setCLKState(false);
		setCLKState(true);
	}
}
