/*
 * Server.h
 *
 *  Created on: 31.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_TCP_SERVER_H_
#define COURIERCXX_NETWORK_TCP_SERVER_H_

#include <event2/bufferevent.h>
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <string>

namespace TCP {

/**
 * TCP server class
 */
class Server {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string ip - ip addr for tcp connection
	 * \param[in] uint16_t port - port for tcp connection
	 * \param[in] func callback - callback for incoming calls
	 */
	Server(std::string ip, uint16_t port, std::function<void (Server* self, int32_t clientFd, std::list<uint8_t>& buffer)> callback);

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
	 * \return int - 0 if success, -1 if error
	 */
	int open();

	/**
	 * Close TCP server
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int close();

	/**
	 * Write data
	 *
	 * \param[in] int32_t clientFd - client socket to write
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(int32_t clientFd, const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data
	 *
	 * \param[in] int32_t clientFd - client socket to write
	 * \param[in] list<uint8_t>& buffer - buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(int32_t clientFd, std::list<uint8_t>& buffer);

	/**
	 * Write data to all clients
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write data to all clients
	 *
	 * \param[in] list<uint8_t>& buffer - buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	int write(std::list<uint8_t>& buffer);

	/**
	 * Read data
	 *
	 * \param[in] int32_t clientFd - client socket to read from
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	int read(int32_t clientFd, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	std::function<void (Server* self, int32_t clientFd, std::list<uint8_t>& buffer)> getCallback();

	/**
	 * Get connected clients
	 *
	 * \return std::map<int32_t, struct bufferevent *> - clients
	 */
	std::map<int32_t, struct bufferevent *>& getConnectedClients();

	/**
	 * Check if server running
	 *
	 * \return bool - true of open, false - otherwise
	 */
	bool isRunning();

private:
	std::string ip;
	uint16_t port = 0;
	std::function<void (Server* self, int32_t clientFd, std::list<uint8_t>& buffer)> callback = nullptr;
	std::map<int32_t, struct bufferevent *> connectedClients;
	bool running = false;
};

} /* namespace TCP */

#endif /* COURIERCXX_NETWORK_TCP_SERVER_H_ */
