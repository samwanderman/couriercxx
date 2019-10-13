/*
 * SCSIPortBase.h
 *
 *  Created on: 25.04.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_SCSI_SCSIPORTBASE_H_
#define COURIERCXX_CONNECTOR_SCSI_SCSIPORTBASE_H_

#include <cstdint>
#include <string>

#include "../IConnectorBase.h"

/**
 * SCSI port
 *
 * FIXME - uncompleted now - may be buggy
 */
class SCSIPortBase: public IConnectorBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string port - path to port
	 */
	SCSIPortBase(std::string port);

	/**
	 * Destructor
	 */
	virtual ~SCSIPortBase();

	/**
	 * Open port
	 *
	 * \return 0 - success, -1 - error
	 */
	int open();

	/**
	 * Close port
	 *
	 * \return 0 - success, -1 - error
	 */
	int close();

	/**
	 * Read data from port
	 *
	 * \param[out] uint8_t* buffer - buffer to store data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to port
	 *
	 * \param[in] const uint8_t* buffer - buffer with data
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Get info from target device
	 *
	 * \param[in] bool extended - show extended info
	 * \param[in] uint8_t pageCode - page code
	 *
	 * \return int - status if success, -1 if error
	 */
	int getDeviceInfo(bool extended, uint8_t pageCode);

private:
	std::string port = "";
	int fd = -1;
};

#endif /* COURIERCXX_CONNECTOR_SCSI_SCSIPORTBASE_H_ */
