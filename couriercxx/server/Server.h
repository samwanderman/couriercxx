/*
 * Server.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_SERVER_SERVER_H_
#define COURIERCXX_SERVER_SERVER_H_

#include <cstdint>
#include <functional>
#include <string>

#include "Request.h"

/**
 * Simple HTTP Server
 */
class Server {
public:
	/**
	 * Server config
	 */
	struct ServerConfig {
		std::string host;
		uint16_t port;
	};
	typedef struct ServerConfig ServerConfig;

	/**
	 * Constructor
	 *
	 * \param[in] config - server config
	 * \param[in] callback - callback on request
	 */
	Server(ServerConfig config, std::function<void (Request&)> callback);

	/**
	 * Destructor
	 */
	virtual ~Server();

	/**
	 * Start server
	 *
	 * \return 0 if success, -1 if error
	 */
	int start();

	/**
	 * Stop server
	 *
	 * \return 0 if success, -1 if error
	 */
	int stop();

private:
	ServerConfig config;
	bool running = false;
	std::function<void (Request&)> callback = nullptr;
};

#endif /* COURIERCXX_SERVER_SERVER_H_ */
