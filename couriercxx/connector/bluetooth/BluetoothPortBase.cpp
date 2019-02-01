/*
 * BluetoothPortBase.cpp
 *
 *  Created on: 28 янв. 2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "BluetoothPortBase.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#define MAX_DEVICES	16
#define SEARCH_TIME	8

BluetoothPortBase::BluetoothPortBase() : IConnectorBase() { }

BluetoothPortBase::BluetoothPortBase(std::string addr) : BluetoothPortBase() {
	this->addr = addr;
}

BluetoothPortBase::~BluetoothPortBase() { }

int BluetoothPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	if (addr.length() == 0) {
		devId = hci_get_route(nullptr);
	} else {
		devId = hci_devid(addr.c_str());
	}

	if (devId == -1) {
		return -1;
	}

	fd = hci_open_dev(devId);
	if (fd == -1) {
		return -1;
	}

	return IConnectorBase::open();
}

int BluetoothPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	::close(fd);
	fd = -1;

	return IConnectorBase::close();
}

std::list<BluetoothDevice*> BluetoothPortBase::search() {
	std::list<BluetoothDevice*> devices;

	int flags = IREQ_CACHE_FLUSH;
	int maxDevices = MAX_DEVICES;

	inquiry_info *foundDevices = (inquiry_info*) malloc(maxDevices * sizeof(inquiry_info));
	int foundDevicesNumber = hci_inquiry(devId, SEARCH_TIME, maxDevices, nullptr, &foundDevices, flags);

	for (int i = 0; i < foundDevicesNumber; i++) {
		char addr[32];
		memset(addr, 0, 32 * sizeof(char));
		ba2str(&foundDevices[i].bdaddr, addr);
		char name[256];
		memset(name, 0, 256 * sizeof(char));
		if (hci_read_remote_name(fd, &foundDevices[i].bdaddr, sizeof(name), name, 0) == 0) {
			uint32_t type = 0;
			type |= foundDevices[i].dev_class[2];
			type |= foundDevices[i].dev_class[1] << 8;
			type |= foundDevices[i].dev_class[0] << 16;
			devices.push_back(new BluetoothDevice(std::string(addr), std::string(name), type));
		}
	}

	free(foundDevices);

	return devices;
}
