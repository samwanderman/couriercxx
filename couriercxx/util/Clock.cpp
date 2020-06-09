/*
 * Clock.cpp
 *
 *  Created on: 13.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Clock.h"

#include <chrono>
#include <cstring>
#include <ctime>
#include <sys/time.h>

#ifdef _WIN32
#include <windows.h>
#endif

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

#ifdef _WIN32
	gmt = 0;
#else
	gmt = t->tm_gmtoff / 3600;
#endif
}

uint64_t Time::getTimestamp() {
    uint16_t year = this->year - 1900;
    uint8_t hour = this->hour;
    uint8_t date = this->date;

    // fix for some cases
    if (year < 70) {
            year = 70;
    }

    if ((year == 70) && (month == 1) && (date <= 1)) {
#ifndef _WIN32
            time_t t = time(nullptr);
            struct tm lt = { 0 };

            localtime_r(&t, &lt);

            if (hour < lt.tm_gmtoff) {
                    hour = lt.tm_gmtoff / 3600;
            }
#endif
            date = 1;
    }

    struct tm time;
    memset(&time, 0, sizeof(time));
    time.tm_sec = second;
    time.tm_min = minute;
    time.tm_hour = hour;
    time.tm_mday = date;
    time.tm_mon = month - 1;
    time.tm_year = year;

#ifndef _WIN32
    time.tm_gmtoff = gmt * 3600;
#endif

	return mktime(&time) * 1000 + msecond;
}

uint64_t Clock::getTimestamp() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	return ms.count();
}

uint64_t Clock::getTimestampExt() {
	microseconds ms = duration_cast<microseconds>(system_clock::now().time_since_epoch());

	return ms.count();
}

int32_t Clock::getTimezoneOffset() {
#ifdef _WIN32
	return 0;
#else
	time_t t = time(nullptr);
	struct tm lt = { 0 };

	localtime_r(&t, &lt);

	return lt.tm_gmtoff / 3600;
#endif
}

int32_t Clock::getDayMinutesFromTimestamp(uint64_t time) {
	time %= 24 * 3600000;
	time = time / 60000;
	time += Clock::getTimezoneOffset() * 60;

	return time;
}

Time Clock::getTime() {
	return Time(getTimestamp());
}

void Clock::setTime(Time newTime) {
#ifdef _WIN32
	SYSTEMTIME time;
	time.wYear			= newTime.year;
	time.wMonth			= newTime.month;
	time.wDay			= newTime.date;
	time.wHour			= newTime.hour;
	time.wMinute		= newTime.minute;
	time.wSecond		= newTime.second;
	time.wMilliseconds	= newTime.msecond;
	SetSystemTime(&time);
#else
	time_t t = newTime.getTimestamp() / 1000;
	stime(&t);
#endif
}

void Clock::setTime(Time time, int32_t timezone) {
#ifdef _WIN32
	setTime(time);
	// TODO - set timezone
#else
	struct timeval t;
	t.tv_usec	= 0;
	t.tv_sec	= time.getTimestamp();

	struct timezone tz;
	tz.tz_dsttime = 0;
	tz.tz_minuteswest = timezone * 60;

	settimeofday(&t, &tz);
#endif
}
