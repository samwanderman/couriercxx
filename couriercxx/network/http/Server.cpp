/*
 * Server.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../../network/http/Server.h"

#include <event2/event_compat.h>
#include <event2/http.h>
#include <event2/http_compat.h>
#include <sys/time.h>
#include <memory>
#include <thread>

#include "../../logger/Log.h"

namespace HTTP {

Server::Server(ServerConfig config, std::function<void (Request&)> callback) {
	this->config = config;
	this->callback = callback;
	running = false;
}

Server::~Server() {
	running = false;
}

int Server::start() {
	if (running) {
		return -1;
	}

	auto func = [this] () {
		if (!event_init()) {
			Log::error("Server: event_init() error");

			return -1;
		}
		Log::debug("Server: event_init() success");

		std::unique_ptr<evhttp, decltype(&evhttp_free)> server(evhttp_start(config.host.c_str(), config.port), &evhttp_free);
		if (!server) {
			Log::error("Server.start() error");

			return -1;
		}
		Log::debug("Server.start() success");

		void (*onRequest)(evhttp_request *request, void* args) = [] (evhttp_request* request, void* args) {
			Server* server = (Server*) args;
			Request serverRequest(request);

			server->callback(serverRequest);
		};

		evhttp_set_gencb(server.get(), onRequest, this);

		if (event_dispatch() == -1) {
			Log::error("Server: event_dispatch() error");

			return -1;
		}
		Log::debug("Server: event_dispatch() success");

		return 0;
	};

	std::thread thread(func);
	thread.detach();

	return 0;
}

int Server::stop() {
	if (!running) {
		return -1;
	}

	struct timeval time;
	time.tv_sec = 0;
	time.tv_usec = 0;
	event_loopexit(&time);

	running = false;

	return 0;
}

};
