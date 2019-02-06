/*
 * BluetoothDevice.h
 *
 *  Created on: 28.01.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_
#define COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_

#include <cstdint>
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
	 * \param[in] uint32_t type - device type
	 */
	BluetoothDevice(std::string addr, std::string name, uint32_t type);

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

	/**
	 * Get device type
	 *
	 * \return uint32_t device type
	 */
	uint32_t getType();

	/**
	 * Connect to found device
	 *
	 * \return 0 if success, -1 if error
	 */
	int connect();

	/**
	 * Disconnect from device
	 *
	 * \return 0 if success, -1 if error
	 */
	int disconnect();

	/**
	 * Read data from device
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max buffer size
	 *
	 * \return num of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to device
	 *
	 * \param[in] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - buffer size
	 *
	 * \return num of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	void test();

private:
	std::string addr = "";
	std::string name = "";
	uint32_t type = 0;
	int sock = -1;
};

#endif /* COURIERCXX_DEVICE_BLUETOOTH_BLUETOOTHDEVICE_H_ */
