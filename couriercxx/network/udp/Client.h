/**
 * Client.h
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_UDP_CLIENT_H_
#define COURIERCXX_NETWORK_UDP_CLIENT_H_

#include <cstdint>
#include <netinet/in.h>
#include <string>

struct event_base;

namespace UDP {

/**
 * UDP client
 */
class Client {
public:
	/**
	 * Constructor
	 *
	 * \param[in] ip	- host ip
	 * \param[in] port	- host port
	 */
	Client(std::string ip, uint16_t port);

	/**
	 * Destructor
	 */
	virtual ~Client();

	Client(const Client &other) = delete;

	Client(Client &&other) = delete;

	Client& operator=(const Client &other) = delete;

	Client& operator=(Client &&other) = delete;

	/**
	 * Open UDP client
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close UDP client
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int close();

	/**
	 * Read data from host
	 *
	 * \param[in, out]	buffer		- pointer to buffer
	 * \param[in]		bufferSize	- max buffer size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(uint8_t* buffer, uint32_t bufferSize);

private:
	std::string			ip			= "";
	uint16_t			port		= 0;

	struct event_base*	base		= nullptr;
	int					fd			= -1;
	struct sockaddr_in	servaddr	= { 0 };

	/**
	 * Clean resources
	 */
	int clean();
};

} /* namespace UDP */

#endif /* COURIERCXX_NETWORK_UDP_CLIENT_H_ */
