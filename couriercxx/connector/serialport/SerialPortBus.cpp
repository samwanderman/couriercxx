/*
 * SerialPortBus.cpp
 *
 *  Created on: 6.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBus.h"

SerialPortBus::SerialPortBus(std::string path, uint32_t baudrate) : SerialPortBase(path, baudrate) { }

SerialPortBus::~SerialPortBus() { }

void SerialPortBus::lock() {
	accessMutex.lock();
}

void SerialPortBus::unlock() {
	accessMutex.unlock();
}