/*
 * SerialPortBusDatasource.cpp
 *
 *  Created on: 12.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBusDatasource.h"

#include "../connector/serialport/SerialPortBus.h"
#include "../logger/Log.h"

SerialPortBusDatasource::SerialPortBusDatasource(SerialPortBus* port) {
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

	return port->open();
}

int SerialPortBusDatasource::disable() {
	Log::debug("SerialPortBusDatasource.disable()");

	return port->close();
}

int SerialPortBusDatasource::read(uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBusDatasource.read()");

	return port->read(buffer, bufferSize);
}

int SerialPortBusDatasource::write(const uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBusDatasource.write()");

	return port->write(buffer, bufferSize);
}

void SerialPortBusDatasource::lock() {
	port->lock();
}

void SerialPortBusDatasource::unlock() {
	port->unlock();
}
