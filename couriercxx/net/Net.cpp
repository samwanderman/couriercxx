/**
 * Net.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Net.h"

#include <ifaddrs.h>
#include <netdb.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstring>

#define DEFAULT_NET_ROUTE		"/proc/net/route"
#define BUFFER_SIZE				32

int Net::getLocalIPAddr(std::string& addr) {
	addr = "";

	Addr address;
	if (get(address) == -1) {
		return -1;
	}

	char name[12];
	memset(name, 0, 12 * sizeof(char));
	snprintf(name, 12, "%hu.%hu.%hu.%hu", address.ip[0], address.ip[1], address.ip[2], address.ip[3]);

	addr = std::string((char*) name);

	return 0;
}

int Net::get(Addr &addr) {
	memset(&addr, 0, sizeof(addr));

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

				sscanf((const char*) name, "%u.%u.%u.%u", (unsigned int*) &addr.ip[0], (unsigned int*) &addr.ip[1], (unsigned int*) &addr.ip[2], (unsigned int*) &addr.ip[3]);

				if (getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in), (char*) name, BUFFER_SIZE, nullptr, 0, NI_NUMERICHOST) != 0) {
					freeifaddrs(ifaddr);

					return -1;
				}

				sscanf((const char*) name, "%u.%u.%u.%u", (unsigned int*) &addr.mask[0], (unsigned int*) &addr.mask[1], (unsigned int*) &addr.mask[2], (unsigned int*) &addr.mask[3]);
			}
		}
	}

	freeifaddrs(ifaddr);

	return 0;
}
