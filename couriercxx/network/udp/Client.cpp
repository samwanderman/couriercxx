/**
 * Client.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Client.h"

#ifdef _WIN32
#else
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include <cstdint>
#include <unistd.h>

#include "../../logger/Log.h"

namespace UDP {

Client::Client(uint16_t port) : Client("", port) { }

Client::Client(std::string ip, uint16_t port) {
	this->ip	= ip;
	this->port	= port;
}

Client::~Client() { }

int Client::open() {
#ifdef _WIN32
#else
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		Log::error("socket() error");

		return -1;
	}

	int yes = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) == -1) {
		Log::error("setsockopt() error");

		clean();

		return -1;
	}

	if (ip.empty()) {
		broadcastAddr					= { 0 };
		broadcastAddr.sin_family		= AF_INET;
		broadcastAddr.sin_addr.s_addr	= htonl(INADDR_BROADCAST);
		broadcastAddr.sin_port			= htons(port);
	}

#endif

	return 0;
}

void Client::clean() {
	if (fd != -1) {
		::close(fd);
		fd = -1;
	}
}

int Client::close() {
	clean();

	return 0;
}

int Client::read(struct sockaddr_in* serverAddr, uint32_t* serverAddrLen, uint8_t* buffer, uint32_t bufferSize) {
#ifdef _WIN32
	return 0;
#else
	return recvfrom(fd, buffer, bufferSize, 0, (struct sockaddr*) serverAddr, (socklen_t*) serverAddrLen);
#endif
}

int Client::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (ip.empty()) {
#ifdef _WIN32
		return 0;
#else
		return sendto(fd, buffer, bufferSize, 0, (struct sockaddr*) &broadcastAddr, sizeof(broadcastAddr));
#endif
	} else {
		return 0;
	}
}

} /* namespace UDP */
