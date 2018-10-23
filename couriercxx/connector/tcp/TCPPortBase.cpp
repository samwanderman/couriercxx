/*
 * TCPPortBase.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../../../couriercxx/connector/tcp/TCPPortBase.h"

#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>

#define PORT_STRING_MAX_LEN	10
#define BUFFER_SIZE 1024

TCPPortBase::TCPPortBase(std::string ip, uint16_t port) : IConnectorBase() {
	this->ip = ip;
	this->port = port;
}

TCPPortBase::TCPPortBase(std::string ip, uint16_t port, std::function<void (TCPPortBase* self, int clientFd, std::list<uint8_t>& buffer)> callback) : TCPPortBase(ip, port) {
	this->callback = callback;
}

TCPPortBase::~TCPPortBase() { }

int TCPPortBase::open() {
	if (callback != nullptr) {
		struct addrinfo *addr = nullptr;
		struct addrinfo defaultAddr;
		memset((void*) &defaultAddr, 0, sizeof(defaultAddr));
		defaultAddr.ai_family = AF_INET;
		defaultAddr.ai_socktype = SOCK_STREAM;
		defaultAddr.ai_protocol = IPPROTO_TCP;
		defaultAddr.ai_flags = AI_PASSIVE;

		char port[PORT_STRING_MAX_LEN];
		memset(port, 0, PORT_STRING_MAX_LEN);
		snprintf(port, PORT_STRING_MAX_LEN - 1, "%i", this->port);
		int res = getaddrinfo(ip.c_str(), port, &defaultAddr, &addr);
		if (res != 0) {
			return -1;
		}

		socketFd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		if (socketFd == -1) {

			return -1;
		}

		res = bind(socketFd, addr->ai_addr, addr->ai_addrlen);
		if (res == -1) {
			_close();

			return -1;
		}

		int option = 1;
		if (setsockopt(socketFd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*) &option, sizeof(option)) == -1) {
			_close();

			return -1;
		}

		if (listen(socketFd, SOMAXCONN) == -1) {
			_close();

			return -1;
		}

		running = true;

		auto func = [this]() {
			while (running) {
				int clientSocket = accept(socketFd, nullptr, nullptr);
				if (clientSocket == -1) {
					continue;
				}

				// REQUEST
				uint8_t buffer[BUFFER_SIZE];
				int bytesRead = ::read(clientSocket, buffer, BUFFER_SIZE);
				if (bytesRead > 0) {
					std::list<uint8_t> bytes(buffer, buffer + bytesRead * sizeof(uint8_t));
					callback(this, clientSocket, bytes);
				}

				::close(clientSocket);
			}

			_close();

			return 0;
		};
		std::thread thread(func);
		thread.detach();
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

		running = true;

		auto func = [this]() {
			while (running) {
				uint8_t buffer[BUFFER_SIZE];
				int bytesRead = ::read(socketFd, buffer, BUFFER_SIZE);
				if (bytesRead > 0) {
					std::list<uint8_t> bytes(buffer, buffer + bytesRead * sizeof(uint8_t));
					callback(this, socketFd, bytes);
				}
			}

			_close();
		};
		std::thread thread(func);
		thread.detach();
	}

	return 0;
}

int TCPPortBase::close() {
	running = false;

	return 0;
}

int TCPPortBase::_close() {
	if (socketFd != -1) {
		::close(socketFd);
	}

	return 0;
}

int TCPPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	return ::write(socketFd, buffer, bufferSize);
}

int TCPPortBase::write(int clientFd, const uint8_t* buffer, uint32_t bufferSize) {
	return ::write(clientFd, buffer, bufferSize);
}

int TCPPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return ::read(socketFd, buffer, bufferSize);
}

int TCPPortBase::read(int clientFd, uint8_t* buffer, uint32_t bufferSize) {
	return ::read(clientFd, buffer, bufferSize);
}
