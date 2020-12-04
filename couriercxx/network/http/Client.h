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
#include <vector>
#include <future>

#include "Http.h"
#include "../../Types.h"

struct event_base;
struct evhttp_connection;

namespace HTTP {

typedef std::function<void(bool error, uint8_t* data, uint32_t dataSize)> ClientCallback;

/**
 * Simple HTTP Client
 */
class Client {
public:
	// client config
	struct ClientConfig {
		std::string	host;
		uint32_t	port	= 0;
		Timeout		timeout = -1;
	};

	struct Response {
		uint32_t				status;
		std::vector<uint8_t>	data;

		Response() : status{0} { }

		Response(uint32_t status) {
			this->status = status;
		}
	};

	/**
	 * Constructor
	 */
	Client(ClientConfig config, ClientCallback callback);

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
	std::promise<Response> send(HTTP::Method method, std::string url, uint8_t* data, uint32_t dataSize);

	/**
	 * Get callback
	 *
	 * \return callback
	 */
	ClientCallback getCallback();

private:
	ClientCallback				callback;
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
