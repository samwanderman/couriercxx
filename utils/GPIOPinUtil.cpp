#ifndef _WIN32

#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <list>

#include "../couriercxx/connector/gpio/GPIOPortBase.h"
#include "../couriercxx/logger/Log.h"
#include "../couriercxx/util/System.h"

class GPIOPortBase;

#define COLOR_ERROR		"\x1b[31m"
#define COLOR_LOG		"\x1b[32m"
#define COLOR_DEBUG		"\x1b[30;1m"
#define COLOR_WARNING	"\x1b[33m"
#define COLOR_RESET		"\x1b[0m"

bool running = false;

void signalHandler(int signal) {
	switch (signal) {
	case SIGHUP:
		break;

	case SIGTERM:
	case SIGINT:
		running = false;

		break;
	}
}

int main(int ac, char**av) {
	Log::setAppName(&av[0][2]);
	Log::info("Program started");

	if (ac < 4) {
		Log::info("%s [offset] [limit] [pin_in_row]", &av[0][2]);

		return 0;
	}

	uint16_t offset = atoi(av[1]);
	uint16_t limit = atoi(av[2]);
	uint16_t pinInRow = atoi(av[3]);

	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = signalHandler;
	sigset_t   set;
	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGHUP);
	act.sa_mask = set;
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGINT, &act, 0);
	sigaction(SIGHUP, &act, 0);

	std::list<GPIOPortBase*> ports;

	for (int i = offset; i < offset + limit; i++) {
		GPIOPortBase port(i, GPIOPortBase::Direction::IN);
		if (port.open() == -1) {
			Log::error("PID %i GPIOPortBase.open() error", i);
		}
		ports.push_back(&port);
	}

	running = true;
	while (running) {
		int i = 0;
		std::list<GPIOPortBase*>::iterator it = ports.begin();
		Log::log("--------------------------\r\n");
		while (it != ports.end()) {
			GPIOPortBase port = *(*it);

			int val = port.getValue();
			if (val > 0) {
				val -= GPIOPortBase::Signal::LOW;
			}

			switch (val) {
			case -1:
				Log::log("%4i (" COLOR_ERROR "%4i" COLOR_RESET ")", port.getPID(), val);

				break;

			case 0:
				Log::log("%4i (%4i)", port.getPID(), val);

				break;

			case 1:
				Log::log("%4i (" COLOR_LOG "%4i" COLOR_RESET ")", port.getPID(), val);

				break;
			}

			if (i % pinInRow == pinInRow - 1) {
				Log::log("\r\n");
			}

			it++;
			i++;
		}
		Log::log("\r\n");

		System::sleep(5000);
	}

	std::list<GPIOPortBase*>::iterator it = ports.begin();
	while (it != ports.end()) {
		GPIOPortBase port = *(*it);
		port.close();

		it++;
	}

	return 0;
}
#else
int main() {
	return 0;
}
#endif
