/**
 * Client.h
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_UDP_CLIENT_H_
#define COURIERCXX_NETWORK_UDP_CLIENT_H_

#ifdef _WIN32
#else
#include <netinet/in.h>
#endif

#include <cstdint>
#include <string>

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
	 * Constructor for broadcast mode
	 *
	 * \param[in] port	- host port
	 */
	Client(uint16_t port);

	/**
	 * Destructor
	 */
	virtual ~Client();

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
	 * \param[out]		serverAddr		- server addr
	 * \param[out]		serverAddrLen	- server addr len
	 * \param[in, out]	buffer			- pointer to buffer
	 * \param[in]		bufferSize		- max buffer size
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(struct sockaddr_in* serverAddr, uint32_t* serverAddrLen, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to host
	 *
	 * \param[in]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- max buffer size
	 *
	 * \return number fo written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

private:
	std::string			ip				= "";
	uint16_t			port			= 0;
	int					fd				= -1;

#ifdef _WIN32
#else
	struct sockaddr_in	broadcastAddr	= { 0 };
#endif

	void clean();
};

} /* namespace UDP */

#endif /* COURIERCXX_NETWORK_UDP_CLIENT_H_ */
