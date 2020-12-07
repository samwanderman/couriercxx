/*
 * SerialPortBaseDatasource.cpp
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBaseDatasource.h"

#include "../connector/serialport/SerialPortBase.h"
#include "../logger/Log.h"

SerialPortBaseDatasource::SerialPortBaseDatasource(SerialPortBase* port) {
	this->port = port;
}

SerialPortBaseDatasource::~SerialPortBaseDatasource() {
	if (port != nullptr) {
		delete port;
		port = nullptr;
	}
}

int SerialPortBaseDatasource::enable() {
	Log::debug("SerialPortBaseDatasource.enable()");

	return port->open();
}

int SerialPortBaseDatasource::disable() {
	Log::debug("SerialPortBaseDatasource.disable()");

	return port->close();
}

int SerialPortBaseDatasource::read(uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBaseDatasource.read()");

	return port->read(buffer, bufferSize);
}

int SerialPortBaseDatasource::read(uint8_t* buffer, uint32_t bufferSize, uint64_t timeout) {
	Log::debug("SerialPortBaseDatasource.read()");

	return port->read(buffer, bufferSize, static_cast<int32_t>(timeout));
}

int SerialPortBaseDatasource::write(const uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("SerialPortBaseDatasource.write()");

	return port->write(buffer, bufferSize);
}
