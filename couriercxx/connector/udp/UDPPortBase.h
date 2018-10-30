/*
 * UDPPortBase.h
 *
 *  Created on: Oct 30, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_UDP_UDPPORTBASE_H_
#define COURIERCXX_CONNECTOR_UDP_UDPPORTBASE_H_

#include <cstdint>
#include <string>

#include <netinet/in.h>

#include "../IConnectorBase.h"

class UDPPortBase : public IConnectorBase {
public:
	/**
	 * Constructor for client usage
	 *
	 * \param[in] string ip - host ip
	 * \param[in] uint16_t port - host port
	 */
	UDPPortBase(std::string ip, uint16_t port);

	/**
	 * Constructor for server usage
	 *
	 * \param[in] uint16_t port - port for udp connection
	 */
	UDPPortBase(uint16_t port);

	UDPPortBase(const UDPPortBase& port) = default;
	UDPPortBase(UDPPortBase&& port) = default;

	/**
	 * Destructor
	 */
	virtual ~UDPPortBase();

	UDPPortBase& operator=(const UDPPortBase& port) = default;
	UDPPortBase& operator=(UDPPortBase&& port) = default;

	/**
	 * Open udp port
	 *
	 * \return 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close udp port
	 *
	 * \return 0 if success, -1 if error
	 */
	int close();

	/**
	 * Write data to udp port
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from udp port
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

private:
	std::string ip = "";
	uint16_t port = 0;
	int fd = -1;
	struct sockaddr_in sin;
};

#endif /* COURIERCXX_CONNECTOR_UDP_UDPPORTBASE_H_ */
