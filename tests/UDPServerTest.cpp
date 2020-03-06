/**
 * UDPTest.cpp
 *
 *  Created on: 26.02.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <cstdlib>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/network/udp/Server.h"
#include "../couriercxx/util/System.h"

#define TIMEOUT	2000

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 2) {
		Log::info("Usage: %s port", &av[0][2]);

		return 0;
	}

	Log::info("Program has started");

	auto func = [](UDP::Server* server, struct sockaddr_in* clientAddr, uint32_t clientAddrLen, const uint8_t* buffer, uint32_t bufferSize) {
		Log::debug("DATA FROM IP: %s, Port: %d", inet_ntoa(clientAddr->sin_addr), ntohs(clientAddr->sin_port));
		uint8_t outBuffer[4] = { 0 };
		outBuffer[0] = 'A';
		outBuffer[1] = 'B';
		outBuffer[2] = 'C';
		server->write(clientAddr, clientAddrLen, outBuffer, sizeof(outBuffer));
		Log::debug("responded");
	};

	UDP::Server* server = new UDP::Server(atoi(av[1]), func);

	if (server->open() == -1) {
		Log::error("UDP.Server.open() error");

		delete server;
		server = nullptr;

		return -1;
	}
	Log::debug("UDP.Server.open() success");

	while (true) {
		System::sleep(TIMEOUT);
	}

	if (server->close() == -1) {
		Log::error("UDP.Server.close() error");
	} else {
		Log::debug("UDP.Serverl.close() success");
	}

	delete server;
	server = nullptr;

	Log::info("Program has finished");

	return 0;
}
