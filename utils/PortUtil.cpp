#include <fcntl.h>
#include <unistd.h>
#include <cstdint>

#include "../couriercxx/logger/Log.h"

#define BUFFER_SIZE	1024

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 2) {
		Log::info("Usage: %s [device]", &av[0][2]);

		return 0;
	}

	Log::info("Starting program");

	int fd = open(av[1], O_RDONLY);
	if (fd == -1) {
		Log::error("open(%s) error", &av[0][2]);

		return -1;
	}
	Log::info("open(%s) success", &av[0][2]);

	uint8_t buffer[BUFFER_SIZE];

	while (true) {
		int res = read(fd, buffer, BUFFER_SIZE);
		Log::info("read %i bytes", res);
		for (int i = 0; i < res; i++) {
			Log::log("%c", buffer[i]);
		}
	}

	close(fd);

	return 0;
}
