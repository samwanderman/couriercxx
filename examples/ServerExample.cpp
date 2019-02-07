#include <cstdint>
#include <string>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/server/Request.h"
#include "../couriercxx/server/Server.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	auto func = [] (Request& request) {
		Log::debug("Server.onRequest()");
		char str[256];
		request.getRAWInput((uint8_t*) str, 256);
		Log::debug("res: %s", str);
		request.writeString("Hello, world!");
		request.send(200, "OK");
	};

	Server::ServerConfig config;
	config.host = "127.0.0.1";
	config.port = 8888;
	Server* server = new Server(config, func);
	int res = server->start();

	if (res == -1) {
		Log::error("Server.start() error");

		delete server;

		return -1;
	}
	Log::debug("Server.start() success");

	if (server->stop() == -1) {
		Log::error("Server.stop() error");

		delete server;

		return -1;
	}
	Log::debug("Server.stop() success");

	delete server;

	return 0;
}
