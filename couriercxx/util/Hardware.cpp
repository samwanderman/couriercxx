/*
 * Hardware.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Hardware.h"

#include <fcntl.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <cstdio>
#include <cstring>

#define DEFAULT_THERMAL_ZONE 	"/sys/class/thermal/thermal_zone0/temp"
#define BUFFER_SIZE				32

float Hardware::getCPUTemperature() {
	float temperature = 0.0f;

#ifndef _WIN32
	int fd = ::open(DEFAULT_THERMAL_ZONE, O_RDONLY);
	if (fd == -1) {
		return 0.0f;
	}

	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE * sizeof(char));
	int res = ::read(fd, buffer, BUFFER_SIZE);
	if (res == -1) {
		::close(fd);

		return 0.0f;
	}
	::close(fd);

	sscanf(buffer, "%f", &temperature);

#endif

	return temperature / 1000.0f;
}
