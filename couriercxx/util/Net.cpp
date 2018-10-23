/*
 * Net.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Net.h"

#include <netdb.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <cstdint>
#include <cstdio>
#include <cstring>

#define DEFAULT_NET_ROUTE		"/proc/net/route"
#define BUFFER_SIZE				32

int Net::getLocalIPAddr(std::string& addr) {
	addr = "";
	FILE* fd = fopen(DEFAULT_NET_ROUTE, "r");
	if (fd == nullptr) {
		return -1;
	}

	const uint16_t bufferMaxSize = 100;
	char buffer[bufferMaxSize], *interfaceName = nullptr, *interfaceDestination = nullptr;

	while (fgets(buffer, bufferMaxSize, fd) != nullptr) {
		interfaceName = strtok(buffer, " \t");
		interfaceDestination = strtok(nullptr, " \t");
		if ((interfaceName != nullptr) && (interfaceDestination != nullptr)) {
			if(strcmp(interfaceDestination, "00000000") == 0) {
				break;
			}
		}
	}

	fclose(fd);

	struct ifaddrs *ifaddr = nullptr;
	if (getifaddrs(&ifaddr) == -1) {
		return -1;
	}

	uint8_t name[BUFFER_SIZE];
	memset(name, 0, sizeof(uint8_t) * BUFFER_SIZE);

	for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == nullptr) {
			continue;
		}

		int family = ifa->ifa_addr->sa_family;

		if (strcmp(ifa->ifa_name , interfaceName) == 0) {
			if (family == AF_INET) {
				if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), (char*) name, BUFFER_SIZE, nullptr, 0, NI_NUMERICHOST) != 0) {
					freeifaddrs(ifaddr);

					return -1;
				}
			}
		}
	}

	freeifaddrs(ifaddr);

	addr = std::string((char*) name);

	return 0;
}
