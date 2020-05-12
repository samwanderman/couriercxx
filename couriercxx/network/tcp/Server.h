/*
 * Server.h
 *
 *  Created on: 31.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_TCP_SERVER_H_
#define COURIERCXX_NETWORK_TCP_SERVER_H_

#include <cstdint>
#include <event2/bufferevent.h>
#include <functional>
#include <map>
#include <string>
#include <vector>

struct evconnlistener;

namespace TCP {

/**
 * TCP server class
 */
class Server {
public:
	/**
	 * Constructor
	 *
	 * \param[in] ip		- ip addr for tcp connection
	 * \param[in] port		- port for tcp connection
	 * \param[in] callback	- callback for incoming calls
	 */
	Server(std::string ip, uint16_t port, std::function<void (Server* self, int32_t clientFd, std::vector<uint8_t>& buffer)> callback);

	/**
	 * Destructor
	 */
	virtual ~Server();

	Server(const Server &other) = default;

	Server(Server &&other) = default;

	Server& operator=(const Server &other) = default;

	Server& operator=(Server &&other) = default;

	/**
	 * Open TCP server
	 *
	 * \return
	 * 			- 0 if success
	 *			- -1 if error
	 */
	int open();

	/**
	 * Close TCP server
	 *
	 * \return
	 * 			- 0 if success
	 *			- -1 if error
	 */
	int close();

	/**
	 * Write data
	 *
	 * \param[in] clientFd	- client socket to write
	 * \param[in] buffer	- buffer to write
	 *
	 * \return
	 * 			- number of written bytes if success
	 * 			- -1 if error
	 */
	int write(int32_t clientFd, std::vector<uint8_t>& buffer);

	/**
	 * Write data to all clients
	 *
	 * \param[in] buffer - buffer to write
	 *
	 * \return
	 * 			- number of written bytes if success
	 * 			- -1 if error
	 */
	int write(std::vector<uint8_t>& buffer);

	/**
	 * Read data
	 *
	 * \param[in]	clientFd	- client socket to read from
	 * \param[out]	buffer		- pointer to buffer
	 *
	 * \return
	 * 			- number of read bytes if success
	 * 			- -1 if error
	 */
	int read(int32_t clientFd, std::vector<uint8_t>& buffer);

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	std::function<void (Server* self, int32_t clientFd, std::vector<uint8_t>& buffer)> getCallback();

	/**
	 * Get connected clients
	 *
	 * \return clients
	 */
	std::map<int32_t, struct bufferevent*>& getConnectedClients();

	/**
	 * Check if server running
	 *
	 * \return
	 * 			- true of open
	 * 			- false - otherwise
	 */
	bool isRunning();

private:
	std::string																			ip;
	uint16_t																			port		= 0;
	bool																				running		= false;
	struct event_base*																	base		= nullptr;
	struct evconnlistener*																listener	= nullptr;
	std::function<void (Server* self, int32_t clientFd, std::vector<uint8_t>& buffer)>	callback	= nullptr;
	std::map<int32_t, struct bufferevent *> connectedClients;
};

} /* namespace TCP */

#endif /* COURIERCXX_NETWORK_TCP_SERVER_H_ */
