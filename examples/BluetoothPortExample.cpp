#include <list>
#include <string>

#include "../couriercxx/connector/bluetooth/BluetoothPortBase.h"
#include "../couriercxx/device/bluetooth/BluetoothDevice.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	BluetoothPortBase *port = new BluetoothPortBase();
	if (port->open() == -1) {
		Log::error("BluetoothPortBase.open() error");

		return -1;
	}
	Log::info("BluetoothPortBase.open() success");

	std::list<BluetoothDevice*> devices = port->search();
	std::list<BluetoothDevice*>::iterator it = devices.begin();

	Log::info("Found %i devices", devices.size());

	while (it != devices.end()) {
		BluetoothDevice* device = *it;
		Log::info("Found device %s on addr %s", device->getName().c_str(), device->getAddr().c_str());

		delete device;

		it++;
	}

	if (port->close() == -1) {
		Log::error("BluetoothPortBase.close() error");

		return -1;
	}
	Log::info("BluetoothPortBase.close() success");

	return 0;
}
