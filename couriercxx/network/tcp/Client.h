/*
 * Client.h
 *
 *  Created on: 31.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_TCP_CLIENT_H_
#define COURIERCXX_NETWORK_TCP_CLIENT_H_

#ifndef _WIN32

#include <cstdint>
#include <condition_variable>
#include <list>
#include <mutex>
#include <string>
#include <vector>
#include <thread>

#include "../../connector/IConnectorBase.h"

struct bufferevent;
struct event_base;

#ifdef _WIN32

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cstdio>

#endif

namespace TCP {

/**
 * TCP client
 */
class Client : public IConnectorBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string ip - ip addr for tcp connection
	 * \param[in] uint16_t port - port for tcp connection
	 */
	Client(std::string ip, uint16_t port);

	/**
	 * Destructor
	 */
	virtual ~Client();

	Client(const Client &other) = default;

	Client(Client &&other) = default;

	Client& operator=(const Client &other) = default;

	Client& operator=(Client &&other) = default;

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
	 * Write data
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data
	 *
	 * \param[in] list<uint8_t>& buffer - buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(std::list<uint8_t>& buffer);

	/**
	 * Read data
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Check if port is open
	 *
	 * \return bool - open state
	 */
	bool isOpen();

	/**
	 * Add data
	 *
	 * \param[in] data - data
	 */
	void addData(std::vector<uint8_t>& data);

private:
	std::string				ip				= "";
	uint16_t				port			= 0;

	bool					opened			= false;
	std::thread				th;

	struct event_base		*base			= nullptr;
	struct bufferevent		*bufferEvent	= nullptr;

	std::vector<uint8_t>	bytes;
	std::mutex				bytesMutex;
	std::condition_variable	bytesVariable;

	std::mutex				writeMutex;

#ifdef _WIN32

	SOCKET				socketFd	= INVALID_SOCKET;

#else

#endif

};

} /* namespace TCP */

#endif

#endif /* COURIERCXX_NETWORK_TCP_CLIENT_H_ */
