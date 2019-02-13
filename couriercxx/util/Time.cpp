/*
 * Time.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Time.h"

#include <ctime>

Time::Time() {
	msecond = 0;
	second = 0;
	minute = 0;
	hour = 0;
	date = 0;
	day = 0;
	month = 0;
	year = 0;
	gmt = 0;
}

Time::Time(uint64_t time) {
	struct tm* t = localtime((time_t*) &time);
	msecond = 0;
	second = t->tm_sec;
	minute = t->tm_min;
	hour = t->tm_hour;
	date = t->tm_mday;
	day = t->tm_wday;
	month = t->tm_mon + 1;
	year = t->tm_year + 1900;
	gmt = 0;
}

uint64_t Time::getTimestamp() {
	struct tm time;
	time.tm_sec = second;
	time.tm_min = minute;
	time.tm_hour = hour;
	time.tm_mday = date;
	time.tm_mon = month - 1;
	time.tm_year = year - 1900;
	time.tm_gmtoff = gmt;

	return (uint64_t) mktime(&time);
}
