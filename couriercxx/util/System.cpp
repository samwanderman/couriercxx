/*
 * System.cpp
 *
 *  Created on: 14.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "System.h"

#include <sys/reboot.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>

int System::startService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl start %s", name.c_str());

	return system(command);
}

int System::stopService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl stop %s", name.c_str());

	return system(command);
}

int System::restartService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl restart %s", name.c_str());

	return system(command);
}

int System::restartNetwork() {
	return system("systemctl restart networking");
}

int System::reboot() {
	return ::reboot(RB_AUTOBOOT);
}

void System::sleep(uint64_t milliseconds) {
	usleep(milliseconds * 1000);
}

void System::usleep(uint64_t microseconds) {
//	::usleep(microseconds);
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}
