/*
 * Clock.cpp
 *
 *  Created on: 13.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Clock.h"

#include <chrono>

#include "Time.h"

using namespace std::chrono;

uint64_t Clock::getTimestamp() {
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	return ms.count();
}

Time Clock::getTime() {
	return Time(getTimestamp());
}
