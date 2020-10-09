#ifndef _WIN32

#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <string>

#include "../couriercxx/connector/serialport/SerialPortBase.h"
#include "../couriercxx/logger/Log.h"
#include "../couriercxx/util/System.h"

#define BUFFER_SIZE	256

void test1(const char* path) {
	int fd = open(path, O_RDWR);
	int flags = fcntl(fd, F_GETFL, 0);

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
		Log::error("fcntl() error");

		close(fd);

		return;
	}

	int res = 0;
	while (true) {
		uint8_t buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE * sizeof(uint8_t));
		res = read(fd, buffer, BUFFER_SIZE);
		Log::debug("Read %i bytes", res);
		for (int i = 0; i < res; i++) {
			Log::log("%02x ", buffer[i]);
		}
		Log::log("\r\n");

		System::sleep(1000);
	}

	close(fd);
}

void test2(const char* path) {
	SerialPortBase::Config config;
	config.nonBlock = true;
	config.timeout = 200;
	config.path = path;

	SerialPortBase port(config);
	if (port.open() == -1) {
		Log::error("SerialPortBase.open() error");

		return;
	}
	Log::info("SerialPortBase.open() success");

	int res = 0;
	while (true) {
		uint8_t buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE * sizeof(uint8_t));
		res = port.read(buffer, BUFFER_SIZE);
		Log::debug("Read %i bytes", res);
		for (int i = 0; i < res; i++) {
			Log::log("%02x ", buffer[i]);
		}
		Log::log("\r\n");

		System::sleep(1000);
	}

	if (port.close() == -1) {
		Log::error("SerialPortBase.close() error");

		return;
	}
	Log::info("SerialPortBase.close() success");
}

int main(int ac, char** av) {
	if (ac < 2) {
		Log::info("Usage: %s [name]", &av[0][2]);

		return 0;
	}

	Log::info("%s start", &av[0][2]);

	test2(av[1]);

	return 0;
}

#else
int main() {
	return 0;
}
#endif
