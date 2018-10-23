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
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
	this->date = 0;
	this->day = 0;
	this->month = 0;
	this->year = 0;
	this->gmt = 0;
}

Time::Time(uint64_t time) {
	struct tm* t = localtime((time_t*) &time);
	this->second = t->tm_sec;
	this->minute = t->tm_min;
	this->hour = t->tm_hour;
	this->date = t->tm_mday;
	this->day = t->tm_wday;
	this->month = t->tm_mon + 1;
	this->year = t->tm_year + 1900;
	this->gmt = 0;
}

uint64_t Time::getTimestamp() {
	struct tm time;
	time.tm_sec = this->second;
	time.tm_min = this->minute;
	time.tm_hour = this->hour;
	time.tm_mday = this->date;
	time.tm_mon = this->month - 1;
	time.tm_year = this->year - 1900;
	time.tm_gmtoff = this->gmt;

	return (uint64_t) mktime(&time);
}
