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

	while (true) {
		uint8_t buffer[BUFFER_SIZE];
		int res = read(fd, buffer, BUFFER_SIZE);
		if (res > 0) {
			Log::debug("read %i bytes", res);

			for (int i = 0; i < res; i++) {
				Log::log("%c ", buffer[i]);
			}

			Log::log("\r\n");
		}
	}

	close(fd);

	return 0;
}
