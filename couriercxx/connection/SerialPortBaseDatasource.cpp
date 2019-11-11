/*
 * SerialPortBaseDatasource.cpp
 *
 *  Created on: 11.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBaseDatasource.h"

#include "../connector/serialport/SerialPortBase.h"

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
	return port->open();
}

int SerialPortBaseDatasource::disable() {
	return port->close();
}

int SerialPortBaseDatasource::read(uint8_t* buffer, uint32_t bufferSize) {
	return port->read(buffer, bufferSize);
}

int SerialPortBaseDatasource::write(const uint8_t* buffer, uint32_t bufferSize) {
	return port->write(buffer, bufferSize);
}
