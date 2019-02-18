/*
 * System.cpp
 *
 *  Created on: 14.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "System.h"

#include <sys/reboot.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int System::startService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl start %s", name.c_str());

	system(command);

	return 0;
}

int System::stopService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl stop %s", name.c_str());

	system(command);

	return 0;
}

int System::restartService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl restart %s", name.c_str());

	system(command);

	return 0;
}

int System::restartNetwork() {
	system("systemctl restart networking");

	return 0;
}

int System::reboot() {
	::reboot(RB_AUTOBOOT);

	return 0;
}
