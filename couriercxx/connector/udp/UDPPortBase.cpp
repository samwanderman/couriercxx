/*
 * UDPPortBase.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "UDPPortBase.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>


UDPPortBase::UDPPortBase(std::string ip, uint16_t port) : IConnectorBase() {
	this->ip = ip;
	this->port = port;
}

UDPPortBase::UDPPortBase(uint16_t port) : UDPPortBase("", port) {
	this->port = port;
}

UDPPortBase::~UDPPortBase() { }

int UDPPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		return -1;
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	// For server usage
	if (ip.empty()) {
		sin.sin_addr.s_addr = htonl(INADDR_ANY);

		if (bind(fd, (struct sockaddr*)&sin, sizeof(sin)) == -1) {
			clean();

			return -1;
		}
	} else {
		if (inet_aton(ip.c_str(), &sin.sin_addr) == 0) {
			return -1;
		}
	}

	return IConnectorBase::open();
}

int UDPPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	clean();

	return IConnectorBase::close();
}

void UDPPortBase::clean() {
	::close(fd);
}

int UDPPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	return sendto(fd, buffer, bufferSize, 0, (sockaddr*) &sin, sizeof(sin));
}

int UDPPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	if (!isOpen()) {
		return -1;
	}

	sockaddr_in serverAddr;
	socklen_t serverAddrSize = sizeof(serverAddr);

	return recvfrom(fd, buffer, bufferSize, 0, (sockaddr*) &serverAddr, &serverAddrSize);
}
