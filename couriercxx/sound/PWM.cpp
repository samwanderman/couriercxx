/*
 * PWM.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "PWM.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "../util/IO.h"

#define PATH_BASE		"/sys/class/pwm/pwmchip%u"
#define PATH_EXPORT		PATH_BASE "/export"
#define PATH_UNEXPORT	PATH_BASE "/unexport"
#define PATH_PERIOD		PATH_BASE "/pwm%u/period"
#define PATH_DUTY_CYCLE	PATH_BASE "/pwm%u/duty_cycle"
#define PATH_ENABLE		PATH_BASE "/pwm%u/enable"

#define STRING_MAX_SIZE	64

#define PERIOD			1000000
#define DUTY_CYCLE		500000

PWM::PWM(uint8_t chipId, uint16_t channelId) {
	this->chipId = chipId;
	this->channelId = channelId;
}

PWM::~PWM() { }

int PWM::open() {
	close();

	char str[STRING_MAX_SIZE];
	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE - 1, PATH_EXPORT, chipId);

	char value[STRING_MAX_SIZE];
	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE - 1, "%u", channelId);

	if (IO::writeTo(str, (uint8_t*) value, strlen(value)) == -1) {
		return -1;
	}

	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE - 1, PATH_PERIOD, chipId, channelId);

	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE - 1, "%u", PERIOD);

	if (IO::writeTo(str, (uint8_t*) value, strlen(value)) == -1) {
		return -1;
	}

	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE -1 , PATH_DUTY_CYCLE, chipId, channelId);

	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE - 1, "%u", DUTY_CYCLE);

	if (IO::writeTo(str, (uint8_t*) value, strlen(value)) == -1) {
		return -1;
	}

	return 0;
}

int PWM::close() {
	char str[STRING_MAX_SIZE];
	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE, PATH_UNEXPORT, chipId);

	char value[STRING_MAX_SIZE];
	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE, "%u", channelId);

	return IO::writeTo(str, (uint8_t*) value, strlen(value));
}

int PWM::play(uint32_t duration) {
	uint8_t enable = 1;

	char str[STRING_MAX_SIZE];
	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE, PATH_ENABLE, chipId, channelId);

	char value[STRING_MAX_SIZE];
	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE, "%u", enable);

	if (IO::writeTo(str, (uint8_t*) value, strlen(value)) == -1) {
		return -1;
	}

	usleep(duration * 1000);

	enable = 0;

	memset(str, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(str, STRING_MAX_SIZE, PATH_ENABLE, chipId, channelId);

	memset(value, 0, STRING_MAX_SIZE * sizeof(char));
	snprintf(value, STRING_MAX_SIZE, "%u", enable);

	if (IO::writeTo(str, (uint8_t*) value, strlen(value)) == -1) {
		return -1;
	}

	return 0;
}
