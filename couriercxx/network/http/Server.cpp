/*
 * Server.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Server.h"

#include <couriercxx/logger/Log.h>
#include <event2/event.h>
#include <event2/http.h>
#include <sys/time.h>
#include <thread>

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
		if ((eventLoop = event_base_new()) == nullptr) {
			Log::error("Server: event_init() error");

			return;
		}
		Log::debug("Server: event_base_new() success");

		server = evhttp_new(eventLoop);
		if (evhttp_bind_socket(server, config.host.c_str(), config.port) == -1) {
			Log::error("Server.start() error");

			evhttp_free(server);
			event_base_free(eventLoop);

			return;
		}
		Log::debug("Server.start() success");

		void (*onRequest)(evhttp_request *request, void* args) = [] (evhttp_request* request, void* args) {
			Server* server = (Server*) args;
			Request serverRequest(request);

			server->callback(serverRequest);
		};

		evhttp_set_gencb(server, onRequest, this);

		if (event_base_dispatch(eventLoop) == -1) {
			Log::error("Server: event_dispatch() error");

			evhttp_free(server);
			event_base_free(eventLoop);

			return;
		}
		Log::debug("Server: event_dispatch() success");
	};

	std::thread thread(func);
	thread.detach();

	return 0;
}

int Server::stop() {
	if (!running) {
		return -1;
	}

	running = false;

	struct timeval time;
	time.tv_sec = 0;
	time.tv_usec = 0;
	event_base_loopexit(eventLoop, &time);

	return 0;
}

};
