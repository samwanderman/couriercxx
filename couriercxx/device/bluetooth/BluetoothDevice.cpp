/*
 * BluetoothDevice.cpp
 *
 *  Created on: 28 янв. 2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "BluetoothDevice.h"

BluetoothDevice::BluetoothDevice(std::string addr, std::string name) : IDevice () {
	this->addr = addr;
	this->name = name;
}

BluetoothDevice::~BluetoothDevice() { }

std::string BluetoothDevice::getAddr() {
	return addr;
}

std::string BluetoothDevice::getName() {
	return name;
}
