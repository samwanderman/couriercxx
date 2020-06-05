#include <cstdint>
#include <string>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/network/http/Request.h"
#include "../couriercxx/network/http/Server.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 3) {
		Log::info("Usage:\r\n$ %s host port", av[0]);

		return 0;
	}

	auto func = [] (HTTP::Request& request) {
		Log::debug("Server.onRequest()");
		char str[256];
		request.getRAWInput((uint8_t*) str, 256);
		Log::debug("res: %s", str);
		request.writeString("Hello, world!");
		request.send(200, "OK");
	};

	HTTP::Server::ServerConfig config;
	config.host = av[1];
	config.port = atoi(av[2]);
	HTTP::Server server(config, func);
	int res = server.start();

	if (res == -1) {
		Log::error("Server.start() error");

		return -1;
	}
	Log::debug("Server.start() success");

	if (server.stop() == -1) {
		Log::error("Server.stop() error");

		return -1;
	}
	Log::debug("Server.stop() success");

	return 0;
}
