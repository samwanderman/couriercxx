/*
 * Client.cpp
 *
 *  Created on: 07.05.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Client.h"

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/http.h>

#include "../../logger/Log.h"

namespace HTTP {

Client::Client(ClientConfig config) {
	Log::debug("Client()");
	this->config = config;
}

Client::~Client() {
	Log::debug("~Client()");
}

int Client::start() {
	Log::debug("Client.start()");

	eventBase = event_base_new();
	if (eventBase == nullptr) {
		Log::error("event_base_new() error");

		clean();

		return -1;
	}

	eventBuffer = bufferevent_socket_new(eventBase, -1, BEV_OPT_CLOSE_ON_FREE);
	if (eventBuffer == nullptr) {
		Log::error("bufferevent_socket_new() error");

		clean();

		return -1;
	}

	connection = evhttp_connection_base_bufferevent_new(eventBase, nullptr, eventBuffer, config.host.c_str(), config.port);
	if (connection == nullptr) {
		Log::error("evhttp_connection_base_bufferevent_new() error");

		clean();

		return -1;
	}

	event_base_dispatch(eventBase);

	return 0;
}

int Client::stop() {
	Log::debug("Client.stop()");

	clean();

	return 0;
}

int Client::send() {
	Log::debug("Client.send()");

	return 0;
}

void Client::clean() {
	Log::debug("Client.clean()");

	if (connection != nullptr) {
		evhttp_connection_free(connection);
		connection = nullptr;
	}

	if (eventBuffer != nullptr) {
		bufferevent_free(eventBuffer);
		eventBuffer = nullptr;
	}

	if (eventBase != nullptr) {
		event_base_free(eventBase);
		eventBase = nullptr;
	}
}

};
