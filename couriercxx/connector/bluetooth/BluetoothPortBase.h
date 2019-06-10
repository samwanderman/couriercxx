/*
 * BluetoothPortBase.h
 *
 *  Created on: 28.01.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_BLUETOOTH_BLUETOOTHPORTBASE_H_
#define COURIERCXX_CONNECTOR_BLUETOOTH_BLUETOOTHPORTBASE_H_

#include <list>
#include <string>

#include "../../device/bluetooth/BluetoothDevice.h"
#include "../IConnectorBase.h"

/**
 * Bluetooth class
 *
 * FIXME - uncompleted now - may be buggy
 */
class BluetoothPortBase : public IConnectorBase {
public:
	/**
	 * Constructor
	 */
	BluetoothPortBase();

	/**
	 * Constructor
	 *
	 * \param[in] string addr - adapter addr
	 */
	BluetoothPortBase(std::string addr);

	/**
	 * Destructor
	 */
	virtual ~BluetoothPortBase();

	/**
	 * Open connector
	 *
	 * \return 0 - success, -1 - error
	 */
	virtual int open();

	/**
	 * Close connector
	 *
	 * \return 0 - success, -1 - error
	 */
	virtual int close();

	/**
	 * Search bluetooth devices
	 *
	 * \return list of bluetooth devices
	 */
	std::list<BluetoothDevice*> search();

	/**
	 * Try connect to service
	 *
	 * \param[in] string addr - device addr
	 * \param[in] uint8_t[16] svcUUIDInt - service UUID
	 *
	 * \return 0 if success, -1 if error
	 */
	int connect(std::string addr, uint8_t svcUUIDInt[16]);

private:
	std::string addr = "";
	int fd = -1;
	int devId = -1;
};

#endif /* COURIERCXX_CONNECTOR_BLUETOOTH_BLUETOOTHPORTBASE_H_ */
