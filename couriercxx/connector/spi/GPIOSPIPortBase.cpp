/*
 * GPIOSPIPortBaseBase.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "GPIOSPIPortBase.h"

#include <cstring>
#include <thread>

#include "../../util/System.h"
#include "../gpio/GPIOPortBase.h"

#define TIMEOUT		20

GPIOSPIPortBase::GPIOSPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs, uint16_t mode) : IConnectorBase() {
	this->mosi = mosi;
	this->miso = miso;
	this->clk = clk;
	this->cs = cs;
	this->mode = mode;
}

GPIOSPIPortBase::GPIOSPIPortBase(int16_t mosi, int16_t miso, int16_t clk, int16_t cs) : GPIOSPIPortBase(mosi, miso, clk, cs, MODE2) { }

GPIOSPIPortBase::~GPIOSPIPortBase() { }

int GPIOSPIPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	gpioMOSI = new GPIOPortBase(mosi, GPIOPortBase::Direction::IN);
	if (gpioMOSI->open() == -1) {
		clean();

		return -1;
	}

	gpioMISO = new GPIOPortBase(miso, GPIOPortBase::Direction::OUT);
	if (gpioMISO->open() == -1) {
		clean();

		return -1;
	}

	gpioCLK = new GPIOPortBase(clk, GPIOPortBase::Direction::OUT);
	if (gpioCLK->open() == -1) {
		clean();

		return -1;
	}

	gpioCS = new GPIOPortBase(cs, GPIOPortBase::Direction::OUT);
	if (gpioCS->open() == -1) {
		clean();

		return -1;
	}
	setCS();

	stopMutex.unlock();
	running = true;
	auto func = [this]() {
		stopMutex.lock();

		while (running) {
			outputBufferMutex.lock();

			if (outputBufferLen > 0) {
				inputBufferMutex.lock();

				for (uint32_t byteIdx = 0; byteIdx < outputBufferLen; byteIdx++) {
					uint8_t outputByte = outputBuffer[byteIdx], inputByte = 0;
					for (int bitIdx = 0; bitIdx < 8; bitIdx++) {
						if (outputByte & 0x80) {
							setMOSI();
						} else {
							clearMOSI();
						}
						outputByte <<= 1;

						delay(TIMEOUT);
						setCLK();

						delay(TIMEOUT);

						inputByte <<= 1;
						inputByte = readMISO();
						clearCLK();
					}

					if (inputBufferLen + 1 > SPI_BUFFER_SIZE) {
						memmove(inputBuffer, &inputBuffer[1], SPI_BUFFER_SIZE - 1);
						inputBufferLen -= 1;
					}

					inputBuffer[inputBufferLen] = inputByte;
					inputBufferLen += 1;
				}

				outputBufferLen = 0;
				inputBufferMutex.unlock();
			}

			outputBufferMutex.unlock();

			delay(TIMEOUT * 10);
		}

		clean();

		stopMutex.unlock();
	};
	std::thread th(func);
	th.detach();

	return IConnectorBase::open();
}

void GPIOSPIPortBase::clean() {
	if (gpioMOSI != nullptr) {
		gpioMOSI->close();
		delete gpioMOSI;
		gpioMOSI = nullptr;
	}

	if (gpioMISO != nullptr) {
		gpioMISO->close();
		delete gpioMISO;
		gpioMISO = nullptr;
	}

	if (gpioCLK != nullptr) {
		gpioCLK->close();
		delete gpioCLK;
		gpioCLK = nullptr;
	}

	if (gpioCS != nullptr) {
		clearCS();
		gpioCS->close();
		delete gpioCS;
		gpioCS = nullptr;
	}
}

int GPIOSPIPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	running = false;

	stopMutex.lock();

	return IConnectorBase::close();
}

int GPIOSPIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	int readBytes = 0;

	inputBufferMutex.lock();

	if (inputBufferLen > 0) {
		readBytes = bufferSize > inputBufferLen ? inputBufferLen : bufferSize;
		memmove(buffer, inputBuffer, readBytes * sizeof(uint8_t));
		memmove(inputBuffer, &inputBuffer[readBytes], inputBufferLen - readBytes);
		inputBufferLen -= readBytes;
	}

	inputBufferMutex.unlock();

	return readBytes;
}

int GPIOSPIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	int writtenBytes = 0;

	outputBufferMutex.lock();

	if (bufferSize > 0) {
		writtenBytes = outputBufferLen + bufferSize > SPI_BUFFER_SIZE ? (SPI_BUFFER_SIZE - outputBufferLen) : bufferSize;
		memmove(&outputBuffer[outputBufferLen], buffer, writtenBytes * sizeof(uint8_t));
		outputBufferLen += writtenBytes;
	}

	outputBufferMutex.unlock();

	return writtenBytes;
}

void GPIOSPIPortBase::setMOSI() {
	gpioMOSI->setValue(GPIOPortBase::Signal::HIGH);
}

void GPIOSPIPortBase::clearMOSI() {
	gpioMOSI->setValue(GPIOPortBase::Signal::LOW);
}

void GPIOSPIPortBase::setCLK() {
	gpioCLK->setValue((mode & 0x2) > 0 ? GPIOPortBase::Signal::HIGH : GPIOPortBase::Signal::LOW);
}

void GPIOSPIPortBase::clearCLK() {
	gpioCLK->setValue((mode & 0x2) > 0 ? GPIOPortBase::Signal::LOW : GPIOPortBase::Signal::HIGH);
}

void GPIOSPIPortBase::setCS() {
	gpioCS->setValue(GPIOPortBase::Signal::LOW);
}

void GPIOSPIPortBase::clearCS() {
	gpioCS->setValue(GPIOPortBase::Signal::HIGH);
}

uint8_t GPIOSPIPortBase::readMISO() {
	return gpioMOSI->getValue() - GPIOPortBase::Signal::LOW;
}

void GPIOSPIPortBase::delay(uint32_t timeout) {
	System::sleep(timeout);
}
