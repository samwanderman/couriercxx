#ifndef _WIN32

#include <list>
#include <string>

#include "../couriercxx/connector/bluetooth/BluetoothPortBase.h"
#include "../couriercxx/device/bluetooth/BluetoothDevice.h"
#include "../couriercxx/logger/Log.h"

int main(int argc, char **argv) {
	Log::setAppName(&argv[0][2]);
	Log::info("Program has started");
	BluetoothPortBase port;

	if (port.open() == -1) {
		Log::error("BluetoothPortBase.open() error");

		return -1;
	}
	Log::info("BluetoothPortBase.open() success");

	std::list<BluetoothDevice*> foundDevices = port.search();
	Log::info("Found %i devices", foundDevices.size());

	std::list<BluetoothDevice*>::iterator it = foundDevices.begin();
	while (it != foundDevices.end()) {
		BluetoothDevice* device = *it;
		Log::info("%s %s", device->getName().c_str(), device->getAddr().c_str());

		uint8_t uuid[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xab, 0xcd };
		port.connect(device->getAddr(), uuid);

		it++;
	}

	it = foundDevices.begin();
	while (it != foundDevices.end()) {
		BluetoothDevice* device = *it;
		delete device;

		it++;
	}

	port.close();

	return 0;
}

#else

int main(){
	return 0;
}

#endif
