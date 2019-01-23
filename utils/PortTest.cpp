/**
 * PortTest.cpp
 *
 *  Created on: 23.01.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include <sys/select.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <cinttypes>
#include <thread>

#include <couriercxx/connector/serialport/SerialPortBase.h>
#include <couriercxx/logger/Log.h>

volatile std::sig_atomic_t running = 1;

void signalHandler(int signal) {
	switch (signal) {
	case SIGHUP:
		break;

	case SIGTERM:
	case SIGINT:
		running = 0;

		break;
	}
}

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);
	Log::info("Start test");

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

	Log::info("Handlers setted");

	for (int i = 1; i < ac; i++) {
		const char* portName = av[i];
		Log::info("%s", portName);
		auto func = [portName]() {
			Log::info("Port %s", portName);

			SerialPortBase *port = new SerialPortBase(portName);
			if (port->open() == -1) {
				Log::error("SerialPortBase.open('%s') error", portName);

				return;
			}
			Log::debug("SerialPort.open('%s') success", portName);

			while (running) {
				uint8_t toWrite[33] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0};

				int res = -1;
				if ((res = port->write(toWrite, 33)) == -1) {
					Log::error("SerialPort.write() error");
				} else {
					Log::debug("SerialPort.write() %i success", res);
				}

				uint8_t toRead[33];
				memset(toRead, 0, sizeof(uint8_t) * 33);
				if ((res = port->read(toRead, 33)) == -1) {
					Log::error("SerialPort.read() error");
				} else {
					Log::debug("SerialPort.read() %i success", res);
				}

				Log::debug("%s", toRead);

				sleep(3);
			}

			port->close();
			Log::info("close %s", portName);
		};

		std::thread th(func);
		th.detach();
	}

	while (running) {
		sleep(3);
	}

	Log::info("Stop test");

	return 0;
}
