/*
 * Client.h
 *
 *  Created on: 31.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_TCP_CLIENT_H_
#define COURIERCXX_NETWORK_TCP_CLIENT_H_

#include <cstdint>
#include <list>
#include <string>

namespace TCP {

/**
 * TCP client
 */
class Client {
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
	 * Check if process running
	 *
	 * \return bool - true if running, false - otherwise
	 */
	bool isRunning();

private:
	std::string ip;
	uint16_t port = 0;
	int socketFd = -1;

	bool running = false;
};

} /* namespace TCP */

#endif /* COURIERCXX_NETWORK_TCP_CLIENT_H_ */
