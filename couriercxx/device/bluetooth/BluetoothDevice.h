/*
 * BluetoothDevice.h
 *
 *  Created on: 28 янв. 2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_
#define COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_

#include <string>

#include "../IDevice.h"

/**
 * Bluetooth device
 */
class BluetoothDevice : public IDevice {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string addr - addr
	 * \param[in] string name - name
	 */
	BluetoothDevice(std::string addr, std::string name);

	/**
	 * Destructor
	 */
	virtual ~BluetoothDevice();

	/**
	 * Get addr
	 *
	 * \return string addr
	 */
	std::string getAddr();

	/**
	 * Get name
	 *
	 * \return string name
	 */
	std::string getName();

private:
	std::string addr = "";
	std::string name = "";
};

#endif /* COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_ */
