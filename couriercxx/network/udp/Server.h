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
#include <string>

struct addrinfo;

namespace UDP {

/**
 * UPD server
 */
class Server {
public:
	/**
	 * Constructor
	 *
	 * \param[in] ip	- ip addr for tcp connection
	 * \param[in] port	- port for tcp connection
	 */
	Server(std::string ip, uint16_t port);

	/**
	 * Destructor
	 */
	virtual ~Server();

	Server(const Server &other) = delete;

	Server(Server &&other) = delete;

	Server& operator=(const Server &other) = delete;

	Server& operator=(Server &&other) = delete;

	/**
	 * Open UDP server
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close UDP server
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int close();

	/**
	 * Check if server is open
	 *
	 * \return bool - true if open, false - otherwise
	 */
	bool isOpen();

	/**
	 * Write data to UDP
	 *
	 * \param[in] buffer		- pointer to buffer
	 * \param[in] bufferSize	- buffer size
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	std::string	ip		= "";
	uint16_t	port	= 0;
	bool		opened	= false;

	int			fd		= -1;
};

} /* namespace UDP */

#endif /* COURIERCXX_NETWORK_UDP_SERVER_H_ */
