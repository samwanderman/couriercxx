	/**
 * Server.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Server.h"

#ifndef _WIN32

#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <cstdint>
#include <unistd.h>
#include <thread>

#include "../../logger/Log.h"

namespace UDP {

#define BUFFER_SIZE	1024

Server::Server(uint16_t port, std::function<void(Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize)> callback) : Server("", port, callback) { }

Server::Server(std::string ip, uint16_t port, std::function<void(Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize)> callback) {
	this->ip		= ip;
	this->port		= port;
	this->callback	= callback;
}

Server::~Server() { }

int Server::open() {
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd == -1) {
		return -1;
	}

	servAddr.sin_family			= AF_INET;
	servAddr.sin_addr.s_addr	= htons(INADDR_ANY);
	servAddr.sin_port			= htons(port);

	int res = bind(fd, (struct sockaddr*) &servAddr, sizeof(servAddr));
	if (res == -1) {
		clean();

		return -1;
	}

	running = true;

	auto func = [this]() {
		int addrLen = sizeof(struct sockaddr_in);
		fd_set readfd;

		while (isRunning()) {
			struct sockaddr_in clientAddr = { 0 };
			FD_ZERO(&readfd);
			FD_SET(fd, &readfd);

			int res = select(fd + 1, &readfd, nullptr, nullptr, 0);
			if (res > 0) {
				if (FD_ISSET(fd, &readfd)) {
					uint8_t buffer[BUFFER_SIZE];
					res = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*) &clientAddr, (socklen_t*) &addrLen);
					if (callback != nullptr) {
						callback(this, &clientAddr, addrLen, buffer, res);
					}
				}
			}
		}
	};
	th = std::thread(func);

	return 0;
}

void Server::clean() {
	if (fd != -1) {
		::close(fd);
		fd = -1;
	}
}

int Server::close() {
	running = false;

	if (th.joinable()) {
		th.join();
	}

	clean();

	return 0;
}

bool Server::isRunning() {
	return running;
}

int Server::read(struct sockaddr_in* clientAddr, uint32_t& clientAddrLen, uint8_t* buffer, uint32_t bufferSize) {
	int res = recvfrom(fd, buffer, bufferSize, 0, (struct sockaddr*) clientAddr, (socklen_t*) &clientAddrLen);
	Log::warn("DATA FROM IP: %s, Port: %d", inet_ntoa(clientAddr->sin_addr), ntohs(clientAddr->sin_port));

	return res;
}

int Server::write(struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize) {
	return sendto(fd, buffer, bufferSize, 0, (struct sockaddr*) clientAddr, clientAddrLen);
}

} /* nameserver */

#endif
