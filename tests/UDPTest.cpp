/**
 * UDPTest.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <cstdint>

#include "couriercxx/logger/Log.h"
#include "couriercxx/network/udp/Server.h"

int main(int ac, char** av) {
	Log::info("%s has started", &av[0][2]);

	UDP::Server* server = new UDP::Server("127.0.0.1", 1888);
	if (server->open() == -1) {
		Log::error("Server.open() error");

		return -1;
	}
	Log::debug("Server.open() success");

	uint8_t data[3] = { 'a', 'b', 'c' };
	if (server->write(data, sizeof(data)) == -1) {
		Log::error("Server.write() error");
		perror("");
	} else {
		Log::debug("Server.write() success");
	}

	if (server->close() == -1) {
		Log::error("Server.close() error");
	} else {
		Log::debug("Server.close() success");
	}

	delete server;

	return 0;
}
