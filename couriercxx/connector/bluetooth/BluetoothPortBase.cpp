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
#include <cstdlib>
#include <unistd.h>

#define MAX_DEVICES	16

BluetoothPortBase::BluetoothPortBase() : IConnectorBase() { }

BluetoothPortBase::BluetoothPortBase(std::string addr) : BluetoothPortBase() {
	this->addr = addr;
}

BluetoothPortBase::~BluetoothPortBase() { }

int BluetoothPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	if (addr.size() == 0) {
		devId = hci_get_route((bdaddr_t*) addr.c_str());
	} else {
		devId = hci_devid(addr.c_str());
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
	int foundDevicesNumber = hci_inquiry(devId, 8, maxDevices, nullptr, &foundDevices, flags);

	if (foundDevicesNumber < 1) {
		return devices;
	}

	for (int i = 0; i < foundDevicesNumber; i++) {
		char addr[32];
		memset(addr, 0, 32 * sizeof(char));
		ba2str(&foundDevices[i].bdaddr, addr);
		char name[256];
		memset(name, 0, 256 * sizeof(char));
		int res = hci_read_remote_name(fd, &foundDevices[i].bdaddr, sizeof(name), name, 0);
	       	if (res == 0) {
			std::string addr1 = std::string(addr);
			std::string name1 = std::string(name);
			devices.push_back(new BluetoothDevice(std::string(addr), std::string(name)));
		}
	}

	free(foundDevices);

	return devices;
}
