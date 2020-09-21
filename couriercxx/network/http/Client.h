/*
 * Client.h
 *
 *  Created on: 07.05.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_HTTP_CLIENT_H_
#define COURIERCXX_NETWORK_HTTP_CLIENT_H_

#include <cstdint>
#include <functional>

#include "Http.h"

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
		const char*	host	= nullptr;
		uint32_t	port	= 0;
		uint32_t	timeout = 0;
	};

	/**
	 * Constructor
	 */
	Client(ClientConfig config, std::function<void(uint8_t* data, uint32_t dataSize)> callback);

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
	 * \param[in] method	- request method
	 * \param[in] url		- request url
	 * \param[in] data		- data to send
	 * \param[in] dataSize	- data size
	 *
	 * \return
	 * 			0	- if success
	 * 			-1	- if error
	 */
	int send(HTTP::Method method, const char* url, uint8_t* data, uint32_t dataSize);

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	std::function<void(uint8_t* data, uint32_t dataSize)> getCallback();

private:
	std::function<void(uint8_t* data, uint32_t dataSize)> callback;
	ClientConfig				config;

	bool						running	= false;

	struct event_base*			base	= nullptr;
	struct evhttp_connection*	conn	= nullptr;

	/**
	 * Clean resources
	 */
	void clean();
};

}; /* namespace HTTP */

#endif /* COURIERCXX_NETWORK_HTTP_CLIENT_H_ */
