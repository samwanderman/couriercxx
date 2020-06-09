/*
 * Client.h
 *
 *  Created on: 07.05.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_HTTP_CLIENT_H_
#define COURIERCXX_NETWORK_HTTP_CLIENT_H_

#ifndef _WIN32

#include <cstdint>
#include <string>

struct bufferevent;
struct event_base;
struct evhttp_connection;

namespace HTTP {

/**
 * Simple HTTP Client
 */
class Client {
public:
	// client config
	struct ClientConfig {
		std::string host = "";
		uint32_t	port = 0;
	};

	/**
	 * Constructor
	 */
	Client(ClientConfig config);

	/**
	 * Destructor
	 */
	virtual ~Client();

	/**
	 * Start client
	 *
	 * \return
	 * 			0	- if success
	 * 			-1	- if error
	 */
	int start();

	/**
	 * Stop server
	 *
	 * \return
	 * 			0	- if success
	 * 			-1	- if error
	 */
	int stop();

	/**
	 * Send request
	 *
	 * \return
	 * 			0	- if success
	 * 			-1	- if error
	 */
	int send();

private:
	ClientConfig config;

	struct event_base*			eventBase	= nullptr;
	struct bufferevent*			eventBuffer	= nullptr;
	struct evhttp_connection*	connection	= nullptr;

	void clean();
};

}; /* namespace HTTP */

#endif

#endif /* COURIERCXX_NETWORK_HTTP_CLIENT_H_ */
