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

#ifdef DEBUG
#include "../../logger/Log.h"
#endif

namespace TCP {

Client::Client(std::string ip, uint16_t port) {
	this->ip = ip;
	this->port = port;
}

Client::~Client() { }

int Client::open() {

#ifdef _WIN32

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		return -1;
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_UNSPEC;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;

	struct addrinfo* result = nullptr;
	char portStr[16];
	memset(portStr, 0, 16);
	itoa(port, portStr, 10);
	if (getaddrinfo(ip.c_str(), portStr, &hints, &result) != 0) {
		WSACleanup();

		return -1;
	}

	struct addrinfo* ptr = nullptr;
	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
		if ((socketFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET) {
			WSACleanup();

			return -1;
		}

		if (connect(socketFd, ptr->ai_addr, (int) ptr->ai_addrlen) == SOCKET_ERROR) {
			closesocket(socketFd);
			socketFd = INVALID_SOCKET;

			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (socketFd == INVALID_SOCKET) {
		WSACleanup();

		return -1;
	}

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

#endif

	opened = true;

	return 0;
}

int Client::close() {

#ifdef _WIN32

	closesocket(socketFd);
	socketFd = INVALID_SOCKET;
	WSACleanup();

#else

	opened = false;

	if (socketFd != -1) {
		::close(socketFd);
	}

	socketFd = -1;

#endif

	return 0;
}

int Client::write(const uint8_t* buffer, uint32_t bufferSize) {

#ifdef _WIN32

	return send(socketFd, (const char*) buffer, bufferSize, 0);

#else

	int res = ::write(socketFd, buffer, bufferSize);

#ifdef DEBUG
	Log::log("> ");
	for (int i = 0; i < res; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n");
#endif

	return res;

#endif

}

int Client::write(std::list<uint8_t>& buffer) {
	std::vector<uint8_t> vec(buffer.begin(), buffer.end());

	return write((const uint8_t*) &vec[0], vec.size());
}

int Client::read(uint8_t* buffer, uint32_t bufferSize) {

#ifdef _WIN32

	return recv(socketFd, (char*) buffer, bufferSize, 0);

#else

	int res = ::read(socketFd, buffer, bufferSize);

#ifdef DEBUG
	Log::log("< ");
	for (int i = 0; i < res; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n");
#endif

	return res;

#endif

}

bool Client::isOpen() {
	return opened;
}

} /* namespace TCP */
