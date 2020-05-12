/*
 * Server.cpp
 *
 *  Created on: 31.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Server.h"

#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <utility>
#include <vector>

#include "../../util/System.h"
#include "../../logger/Log.h"

namespace TCP {

#define BUFFER_SIZE			1024

void echoReadCallback(struct bufferevent *buffEvent, void *arg) {
	Log::debug("TCP.Server.echoReadCallback()");

	Server* self = reinterpret_cast<Server*>(arg);

	struct evbuffer *inputBuffer = bufferevent_get_input(buffEvent);
	uint32_t len = evbuffer_get_length(inputBuffer);

	std::vector<uint8_t> bytes(len);

	int bytesRead = evbuffer_remove(inputBuffer, &bytes[0], len);
	Log::debug("read %i bytes", bytesRead);

	self->getCallback()(self, static_cast<int32_t>(bufferevent_getfd(buffEvent)), bytes);
}

void echoEventCallback(struct bufferevent *buffEvent, short events, void *arg) {
	Log::debug("TCP.Server.echoEventCallback()");

	Server* self = reinterpret_cast<Server*>(arg);

	if (events & BEV_EVENT_ERROR) {
		Log::error("Error of bufferevent object");
	}

	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		Log::debug("Clear events");

		int32_t fd = static_cast<int32_t>(bufferevent_getfd(buffEvent));
		self->getConnectedClients().erase(fd);

		bufferevent_free(buffEvent);
	}
}

void acceptConnectionCallback(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int sockLen, void *arg ) {
	Log::debug("TCP.Server.acceptConnectionCallback()");
	Server* self = reinterpret_cast<Server*>(arg);

	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *buffEvent = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	bufferevent_setcb(buffEvent, echoReadCallback, nullptr, echoEventCallback, arg);
	bufferevent_enable(buffEvent, EV_READ | EV_WRITE);

	self->getConnectedClients().insert(std::pair<int32_t, struct bufferevent *>(static_cast<int32_t>(fd), buffEvent));
}

void acceptErrorCallback(struct evconnlistener *listener, void *arg) {
	struct event_base *base = evconnlistener_get_base(listener);
	event_base_loopexit(base, nullptr);
}

Server::Server(std::string ip, uint16_t port, std::function<void (Server* self, int32_t clientFd, std::vector<uint8_t>& buffer)> callback) {
	this->ip		= ip;
	this->port		= port;
	this->callback	= callback;
}

Server::~Server() { }

int Server::open() {
	Log::debug("TCP.Server.open()");

	running = true;

	auto func = [this]() {
		Log::debug("Try to start TCP.Server");
		struct sockaddr_in sin;

		base = event_base_new();
		if (!base) {
			return -1;
		}

		memset(&sin, 0, sizeof(sin));
		sin.sin_family		= AF_INET;
		sin.sin_addr.s_addr = htonl(INADDR_ANY);
		sin.sin_port		= htons(this->port);

		while (isRunning() && ((listener = evconnlistener_new_bind(base, acceptConnectionCallback, this, (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE), -1, (struct sockaddr*) &sin, sizeof(sin))) == nullptr)) {
			System::sleep(5000);
		}
		evconnlistener_set_error_cb(listener, acceptErrorCallback);

		event_base_dispatch(base);

		return 0;
	};

	std::thread th(func);
	th.detach();

	return 0;
}

int Server::close() {
	Log::debug("TCP.Server.close()");

	running = false;

	if (listener != nullptr) {
		evconnlistener_free(listener);
		listener = nullptr;
	}

	if (callback != nullptr) {
		struct timeval time;
		time.tv_sec		= 0;
		time.tv_usec	= 0;
		event_base_loopexit(base, &time);
	}

	std::map<int, struct bufferevent *>::iterator it = connectedClients.begin();
	while (it != connectedClients.end()) {
		bufferevent_free(it->second);

		it++;
	}

	connectedClients.clear();

	return 0;
}

int Server::write(int32_t clientFd, std::vector<uint8_t>& buffer) {
	return ::write(clientFd, &buffer[0], buffer.size());
}

int Server::read(int32_t clientFd, std::vector<uint8_t>& buffer) {
	return ::read(clientFd, &buffer[0], buffer.size());
}

int Server::write(std::vector<uint8_t>& buffer) {
	std::map<int32_t, struct bufferevent *>::iterator it = connectedClients.begin();
	while (it != connectedClients.end()) {
		write(it->first, buffer);

		it++;
	}

	return 0;
}

std::function<void (Server* self, int32_t clientFd, std::vector<uint8_t>& buffer)> Server::getCallback() {
	return callback;
}

std::map<int32_t, struct bufferevent *>& Server::getConnectedClients() {
	return connectedClients;
}

bool Server::isRunning() {
	return running;
}

} /* namespace TCP */
