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
	time_t t = time(nullptr);
	struct tm lt = { 0 };
	localtime_r(&t, &lt);

	return lt.tm_gmtoff / 3600;
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

