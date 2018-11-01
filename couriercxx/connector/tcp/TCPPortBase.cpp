/*
 * TCPPortBase.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "TCPPortBase.h"

#include <arpa/inet.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/event_compat.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <thread>

#include "../../logger/Log.h"

struct event_base;

#define PORT_STRING_MAX_LEN	10
#define BUFFER_SIZE			1024

void echoReadCallback(struct bufferevent *buffEvent, void *arg) {
	TCPPortBase* self = (TCPPortBase*) arg;

	struct evbuffer *inputBuffer = bufferevent_get_input(buffEvent);
	uint8_t buffer[BUFFER_SIZE];
	int bytesRead = evbuffer_remove(inputBuffer, buffer, BUFFER_SIZE);

	std::list<uint8_t> bytes;
	for (int i = 0; i < bytesRead; i++) {
		bytes.push_back(buffer[i]);
	}

	self->getCallback()(self, bufferevent_getfd(buffEvent), bytes);
}

void echoEventCallback(struct bufferevent *buffEvent, short events, void *arg) {
	if (events & BEV_EVENT_ERROR) {
		Log::error("Error of bufferevent object");
	}

	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		bufferevent_free(buffEvent);
	}
}

void acceptConnectionCallback(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int sockLen, void *arg ) {
  struct event_base *base = evconnlistener_get_base(listener);
  struct bufferevent *buffEvent = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

  bufferevent_setcb(buffEvent, echoReadCallback, nullptr, echoEventCallback, arg);
  bufferevent_enable(buffEvent, EV_READ | EV_WRITE);
}

void acceptErrorCallback(struct evconnlistener *listener, void *arg) {
  struct event_base *base = evconnlistener_get_base(listener);
  event_base_loopexit(base, nullptr);
}

TCPPortBase::TCPPortBase(std::string ip, uint16_t port) : IConnectorBase() {
	this->ip = ip;
	this->port = port;
}

TCPPortBase::TCPPortBase(std::string ip, uint16_t port, std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> callback) : TCPPortBase(ip, port) {
	this->callback = callback;
}

TCPPortBase::~TCPPortBase() { }

int TCPPortBase::open() {
	if (IConnectorBase::open() == -1) {
		return -1;
	}

	if (callback != nullptr) {
		auto func = [this]() {
			struct event_base* base;
			struct evconnlistener* listener;
			struct sockaddr_in sin;

			base = event_base_new();
			if (!base) {
				return -1;
			}

			memset(&sin, 0, sizeof(sin));
			sin.sin_family = AF_INET;
			sin.sin_addr.s_addr = htonl(INADDR_ANY);
			sin.sin_port = htons(this->port);

			listener = evconnlistener_new_bind(base, acceptConnectionCallback, this, (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE), -1, (struct sockaddr*) &sin, sizeof(sin));
			if (!listener) {
				return -1;
			}
			evconnlistener_set_error_cb(listener, acceptErrorCallback);

			event_base_dispatch(base);

			return 0;
		};

		std::thread th(func);
		th.detach();
	} else {
		socketFd = socket(AF_INET, SOCK_STREAM, 0);
		if (socketFd == -1) {
			return -1;
		}

		struct sockaddr_in servAddr;
		memset(&servAddr, '0', sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(port);

		if (inet_pton(AF_INET, ip.c_str(), &servAddr.sin_addr) != 1) {
			_close();

			return -1;
		}

		if (connect(socketFd, (struct sockaddr*) &servAddr, sizeof(servAddr)) == -1) {
			_close();

			return -1;
		}
	}

	return 0;
}

std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> TCPPortBase::getCallback() {
	return callback;
}

int TCPPortBase::close() {
	if (IConnectorBase::close() == -1) {
		return -1;
	}

	if (callback != nullptr) {
		struct timeval time;
		time.tv_sec = 0;
		time.tv_usec = 0;
		event_loopexit(&time);
	}

	return _close();
}

int TCPPortBase::_close() {
	if (socketFd != -1) {
		::close(socketFd);
	}

	return 0;
}

int TCPPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::write(socketFd, buffer, bufferSize);
}

int TCPPortBase::write(int clientFd, const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::write(clientFd, buffer, bufferSize);
}

int TCPPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::read(socketFd, buffer, bufferSize);
}

int TCPPortBase::read(int clientFd, uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return ::read(clientFd, buffer, bufferSize);
}
