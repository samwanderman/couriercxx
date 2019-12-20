/*
 * Client.cpp
 *
 *  Created on: 31.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../../network/tcp/Client.h"

#ifdef _WIN32
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include <unistd.h>
#include <cstring>
#include <vector>

namespace TCP {

Client::Client(std::string ip, uint16_t port) {
	this->ip = ip;
	this->port = port;
}

Client::~Client() { }

int Client::open() {
#ifdef _WIN32
#else
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1) {
		return -1;
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);

	if (inet_pton(AF_INET, ip.c_str(), &servAddr.sin_addr) != 1) {
		close();

		return -1;
	}

	if (connect(socketFd, (struct sockaddr*) &servAddr, sizeof(servAddr)) == -1) {
		close();

		return -1;
	}

	running = true;

	return 0;
#endif

	return -1;
}

int Client::close() {
#ifdef _WIN32
#else
	running = false;

	if (socketFd != -1) {
		::close(socketFd);
	}

	socketFd = -1;
#endif
	return 0;
}

int Client::write(const uint8_t* buffer, uint32_t bufferSize) {
#ifdef _WIN32
	return 0;
#else
	return ::write(socketFd, buffer, bufferSize);
#endif
}

int Client::write(std::list<uint8_t>& buffer) {
	std::vector<uint8_t> vec(buffer.begin(), buffer.end());

	return write((const uint8_t*) &vec[0], vec.size());
}

int Client::read(uint8_t* buffer, uint32_t bufferSize) {
#ifdef _WIN32
	return -1;
#else
	return ::read(socketFd, buffer, bufferSize);
#endif
}

bool Client::isRunning() {
	return running;
}

} /* namespace TCP */
