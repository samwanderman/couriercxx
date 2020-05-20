/**
 * Net.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../network/Net.h"

#ifdef _WIN32
#else
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/socket.h>
#endif
#include <cstdio>
#include <cstring>
#include <list>

#include "../util/String.h"

class String;

#define DEFAULT_NET_ROUTE		"/proc/net/route"
#define BUFFER_SIZE				32

int getGateway(uint8_t gateway[4]) {
	FILE *fp = popen("ip route show", "r");

	char line[256];
	memset(line, 0, 256 * sizeof(char));

	bool parsed = false;
	while ((fgets(line, sizeof(line), fp) != nullptr) && !parsed) {
		std::list<std::string> parts = String::split(line, " ");
		std::list<std::string>::iterator it = parts.begin();
		int i = 0;
		while (it != parts.end()) {
			std::string part = *it;
			if ((i == 0) && (part == "default")) {
				parsed = true;
			}

			if (i == 2) {
				sscanf(part.c_str(), "%hu.%hu.%hu.%hu", (short unsigned int*) &gateway[0], (short unsigned int*) &gateway[1], (short unsigned int*) &gateway[2], (short unsigned int*) &gateway[3]);

				break;
			}

			i++;
			it++;
		}
	}

	pclose(fp);

	return 0;
}

int Net::getLocalIPAddr(std::string& addr) {
	addr = "";

	Addr address;
	if (get(address) == -1) {
		return -1;
	}

	char name[32];
	memset(name, 0, 32 * sizeof(char));
	snprintf(name, 31, "%hu.%hu.%hu.%hu", address.ip[0], address.ip[1], address.ip[2], address.ip[3]);

	addr = std::string((char*) name);

	return 0;
}

int Net::get(Addr &addr) {

#ifdef _WIN32

#else

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

				getGateway(addr.gateway);
			}
		}
	}

	freeifaddrs(ifaddr);

#endif

	return 0;
}

std::string Net::ipToStr(uint8_t ip[4]) {
	char buffer[20];
	memset(buffer, 0, sizeof(buffer));
	snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);

	return std::string(buffer);
}
