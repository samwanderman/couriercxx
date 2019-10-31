/*
 * TCPPortBase.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTOR_TCP_TCPPORTBASE_H_
#define COURIERCXX_CONNECTOR_TCP_TCPPORTBASE_H_

#include <cstdint>
#include <functional>
#include <list>
#include <string>

#include "../IConnectorBase.h"

class TCPPortBase : public IConnectorBase {
public:
	/**
	 * Constructor for server usage
	 *
	 * \param[in] string ip - ip addr for tcp connection
	 * \param[in] uint16_t port - port for tcp connection
	 * \param[in] func callback - callback for incoming calls
	 */
	TCPPortBase(std::string ip, uint16_t port, std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> callback);

	/**
	 * Constructor for client usage
	 *
	 * \param[in] string ip - ip addr for tcp connection
	 * \param[in] uint16_t port - port for tcp connection
	 */
	TCPPortBase(std::string ip, uint16_t port);

	TCPPortBase(const TCPPortBase& port) = default;
	TCPPortBase(TCPPortBase&& port) = default;

	/**
	 * Destructor
	 */
	virtual ~TCPPortBase();

	TCPPortBase& operator=(const TCPPortBase& port) = default;
	TCPPortBase& operator=(TCPPortBase&& port) = default;

	/**
	 * Open tcp port
	 *
	 * \return 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close tcp port
	 *
	 * \return 0 if success, -1 if error
	 */
	int close();

	/**
	 * Write data to tcp port
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to tcp port
	 *
	 * \param[in] list<uint8_t>& buffer - buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(std::list<uint8_t>& buffer);

	/**
	 * Write data to tcp port
	 *
	 * \param[in] int clientFd - client socket to write
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(int clientFd, const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to tcp port
	 *
	 * \param[in] int clientFd - client socket to write
	 * \param[in] list<uint8_t>& buffer - buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(int clientFd, std::list<uint8_t>& buffer);

	/**
	 * Read data from tcp port
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from tcp port
	 *
	 * \param[in] int clientFd - client socket to read from
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(int clientFd, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> getCallback();

private:
	std::string ip = "";
	uint16_t port = 0;
	std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> callback = nullptr;

	int socketFd = -1;

	void clean();
};

#endif /* COURIERCXX_CONNECTOR_TCP_TCPPORTBASE_H_ */
