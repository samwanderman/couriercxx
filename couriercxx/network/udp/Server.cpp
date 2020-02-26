/**
 * Server.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Server.h"

#include <cstdint>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>

#include "../../logger/Log.h"

namespace UDP {

Server::Server(std::string ip, uint16_t port) {
	this->ip	= ip;
	this->port	= port;
}

Server::~Server() { }

int Server::open() {
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		Log::error("UDP.Server: socket() error");

		close();

		return -1;
	}

	struct sockaddr_in addr = { 0 };
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= INADDR_ANY;
	addr.sin_port			= htons(port);

	if (bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) == -1) {
		Log::error("UDP.Server: bind() error");

		close();

		return -1;
	}

	opened = true;

	return 0;
}

int Server::close() {
	opened = false;

	if (fd != -1) {
		::close(fd);
		fd = -1;
	}

	return 0;
}

bool Server::isOpen() {
	return opened;
}

int Server::write(const uint8_t* buffer, uint32_t bufferSize) {
	return ::write(fd, buffer, bufferSize);
}

} /* nameserver */
