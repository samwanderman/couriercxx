/**
 * UDPClientTest.cpp
 *
 *  Created on: 06.03.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/network/udp/Client.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	UDP::Client* client = nullptr;

	if (ac < 2) {
		Log::info("Usage: %s [host] port string", &av[0][2]);

		return 0;
	}

	Log::info("Program had started");

	const char* str = "";

	if (ac == 3) {
		client = new UDP::Client(atoi(av[1]));
		str = av[2];
	} else if (ac >= 4) {
		client = new UDP::Client(std::string(av[1]), atoi(av[2]));
		av[3];
	}

	if (client->open() == -1) {
		Log::error("UDP.Client.open() error");

		delete client;

		return -1;
	}
	Log::debug("UDP.Client.open() success");

	Log::debug("Send %s", str);
	int res = client->write((const uint8_t*) str, strlen(str));
	Log::debug("%i bytes written", res);
	for (int i = 0; i < res; i++) {
		Log::log("%c", str[i]);
	}
	Log::log("\r\n");

	struct sockaddr_in* serverAddr = nullptr;
	uint32_t serverAddrLen = 0;
	uint8_t buffer[1024];
	res = client->read(serverAddr, &serverAddrLen, buffer, sizeof(buffer));
	Log::debug("%i bytes read", res);
	for (int i = 0; i < res; i++) {
		Log::log("%c", buffer[i]);
	}
	Log::log("\r\n");

	if (client->close() == -1) {
		Log::error("UDP.Client.close() error");

		delete client;

		return -1;
	}
	Log::debug("UDP.Client.close() success");

	Log::info("Program had finished");

	return 0;
}
