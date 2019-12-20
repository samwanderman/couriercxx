/*
 * System.cpp
 *
 *  Created on: 14.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "System.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/reboot.h>
#endif
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
#ifndef _WIN32
	return ::reboot(RB_AUTOBOOT);
#else
	return 0;
#endif
}

void System::sleep(uint64_t milliseconds) {
	usleep(milliseconds * 1000);
}

void System::usleep(uint64_t microseconds) {
#ifdef _WIN32
	Sleep(microseconds/ 1000);
#else
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}

int System::mkdir(std::string path) {
	char command[256];
	memset(command, 0, sizeof(command));
	snprintf(command, 255, "mkdir -p %s", path.c_str());

	return system(command);
}
