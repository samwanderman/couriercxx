/*
 * SerialPortBusDatasource.cpp
 *
 *  Created on: 12.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBusDatasource.h"

#include <thread>
#include <cinttypes>

#include "../connector/serialport/SerialPortBus.h"
#include "../logger/Log.h"
#include "../util/System.h"

#define TIMEOUT_RECONNECT	5000

SerialPortBusDatasource::SerialPortBusDatasource(SerialPortBus* port) : IConcurrentDatasource() {
	this->port = port;
}

SerialPortBusDatasource::~SerialPortBusDatasource() {
	if (port != nullptr) {
		delete port;
		port = nullptr;
	}
}

int SerialPortBusDatasource::enable() {
	Log::debug("SerialPortBusDatasource.enable()");

	if (running) {
		return 0;
	}

	running = true;
	stopMutex.unlock();

	if (port->open() == -1) {
		// async connect
		auto connectFunc = [this]() {
			stopMutex.lock();

			while (running && (port->open() == -1)) {
				System::sleep(TIMEOUT_RECONNECT);
			}

			stopMutex.unlock();
		};
		std::thread th(connectFunc);
		th.detach();
	}

	return 0;
}

int SerialPortBusDatasource::disable() {
	Log::debug("SerialPortBusDatasource.disable()");

	if (!running) {
		return 0;
	}

	running = false;

	stopMutex.lock();

	if (port->isOpen()) {
		return port->close();
	}

	return 0;
}

int SerialPortBusDatasource::read(uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBusDatasource.read()");

	if (running && port->isOpen()) {
		int res = port->read(buffer, bufferSize);

		if (res >= 0) {
			return res;
		}

		disable();
		enable();
	}

	return -1;
}

int SerialPortBusDatasource::read(uint8_t* buffer, uint32_t bufferSize, uint64_t timeout) {
	Log::debug("SerialPortBusDatasource.read() with timeout %" PRIu64, timeout);

	if (running && port->isOpen()) {
		int res = port->read(buffer, bufferSize, timeout);

		if (res >= 0) {
			return res;
		}

		disable();
		enable();
	}

	return -1;
}

int SerialPortBusDatasource::write(const uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBusDatasource.write()");

	if (running && port->isOpen()) {
		int res = port->write(buffer, bufferSize);

		if (res >= 0) {
			return res;
		}

		disable();
		enable();
	}

	return -1;
}

void SerialPortBusDatasource::lock() {
	port->lock();
}

void SerialPortBusDatasource::unlock() {
	port->unlock();
}
