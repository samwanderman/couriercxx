/**
 * Server.h
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_UDP_SERVER_H_
#define COURIERCXX_NETWORK_UDP_SERVER_H_

#include <cstdint>
#include <netinet/in.h>
#include <functional>
#include <mutex>
#include <string>

namespace UDP {

/**
 * UDP server
 */
class Server {
public:
	/**
	 * Constructor
	 *
	 * \param[in]		ip			- ip addr for tcp connection
	 * \param[in]		port		- port for tcp connection
	 * \param[in]		callback	- callback
	 */
	Server(std::string ip, uint16_t port, std::function<void(Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize)> callback);

	/**
	 * Constructor
	 *
	 * \param[in]		port		- port for tcp connection
	 * \param[in]		callback	- callback
	 */
	Server(uint16_t port, std::function<void(Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize)> callback);

	/**
	 * Destructor
	 */
	virtual ~Server();

	/**
	 * Open UDP server
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int open();

	/**
	 * Check if server is running
	 *
	 * \return true if server running, false - otherwise
	 */
	bool isRunning();

	/**
	 * Close UDP server
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int close();

	/**
	 * Read data from port
	 *
	 * \param[in]		clientAddr		- client addr
	 * \param[in]		clientAddrLen	- client addr len
	 * \param[in, out]	buffer			- pointer to buffer
	 * \param[in]		bufferSize		- buffer size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(struct sockaddr_in* clientAddr, uint32_t& clientAddrLen, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write buffer to client
	 *
	 * \param[in] clientAddr		- client to write
	 * \param[in] clientAddrLen		- client add len
	 * \param[in] buffer			- pointer to buffer with data
	 * \param[in] bufferSize		- buffer size
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize);

private:
	std::string			ip			= "";
	uint16_t			port		= 0;
	int					fd			= -1;
	struct sockaddr_in	servAddr	= { 0 };

	std::function<void(Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize)> callback = nullptr;

	bool				running		= false;
	std::mutex			stopMutex;

	void clean();
};

} /* namespace UDP */

#endif /* COURIERCXX_NETWORK_UDP_SERVER_H_ */
