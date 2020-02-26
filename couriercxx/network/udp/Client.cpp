/**
 * Client.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Client.h"

#include <cstdint>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../logger/Log.h"

namespace UDP {

#define BUFFER_SIZE	1024

void readCallback(int fd, short int y, void *args) {
	Log::debug("readCallback()");

	uint8_t buffer[BUFFER_SIZE];

	int readBytes = ::read(fd, buffer, sizeof(buffer));
	Log::debug("read %i bytes");

	Log::log("> ");
	for (int i = 0; i < readBytes; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n");
}

Client::Client(std::string ip, uint16_t port) {
	this->ip	= ip;
	this->port	= port;
}

Client::~Client() { }

int Client::open() {
	// start base event loop
	base = event_base_new();
	if (base == nullptr) {
		Log::error("UDP.Client: event_base_new() error");

		clean();

		return -1;
	}

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		Log::error("UDP.Client: socket() error");

		clean();

		return -1;
	}

	servaddr.sin_family			= AF_INET;
	servaddr.sin_port			= htons(port);
	servaddr.sin_addr.s_addr	= INADDR_ANY;

	struct event udpEvent;
	event_assign(&udpEvent, base, fd, EV_READ | EV_PERSIST, readCallback, this);
	event_add(&udpEvent, nullptr);

	if (event_base_dispatch(base) != 0) {
		Log::error("UDP.Client: event_base_dispatch() error");

		clean();

		return -1;
	}

	return 0;
}

int Client::clean() {
	if (base != nullptr) {
		struct timeval time = { 0 };
		event_base_loopexit(base, &time);
		event_base_free(base);
		base = nullptr;
	}

	if (fd != -1) {
		::close(fd);
		fd = -1;
	}

	return 0;
}

int Client::close() {
	clean();

	return 0;
}

int Client::read(uint8_t* buffer, uint32_t bufferSize) {
	socklen_t len = 0;
	return recvfrom(fd, buffer, bufferSize, MSG_WAITALL, (struct sockaddr*) &servaddr, &len);
}

} /* namespace UDP */
