/*
 * Clock.cpp
 *
 *  Created on: 13.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Clock.h"

#include <chrono>
#include <cstring>
#include <ctime>

using namespace std::chrono;

Time::Time() { }

Time::Time(uint64_t time) {
	msecond = time % 1000;

	time /= 1000;
	struct tm* t = localtime((time_t*) &time);
	second = t->tm_sec;
	minute = t->tm_min;
	hour = t->tm_hour;
	date = t->tm_mday;
	day = t->tm_wday;
	month = t->tm_mon + 1;
	year = t->tm_year + 1900;
	gmt = t->tm_gmtoff / 3600;
}

uint64_t Time::getTimestamp() {
	struct tm time;
	memset(&time, 0, sizeof(time));
	time.tm_sec = second;
	time.tm_min = minute;
	time.tm_hour = hour;
	time.tm_mday = date;
	time.tm_mon = month - 1;
	time.tm_year = year - 1900;
	time.tm_gmtoff = gmt * 3600;

	return mktime(&time) * 1000;
}

uint64_t Clock::getTimestamp() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	return ms.count();
}

uint64_t Clock::getTimestampExt() {
	microseconds ms = duration_cast<microseconds>(system_clock::now().time_since_epoch());

	return ms.count();
}

Time Clock::getTime() {
	return Time(getTimestamp());
}

void Clock::setTime(Time newTime) {
	time_t t = newTime.getTimestamp() / 1000;
    stime(&t);
}

