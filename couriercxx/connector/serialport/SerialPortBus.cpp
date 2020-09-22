/*
 * SerialPortBus.cpp
 *
 *  Created on: 6.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SerialPortBus.h"

SerialPortBus::SerialPortBus(SerialPortBase::Config config) : SerialPortBase(config) { }

SerialPortBus::~SerialPortBus() { }

void SerialPortBus::lock() {
	accessMutex.lock();
}

void SerialPortBus::unlock() {
	accessMutex.unlock();
}
