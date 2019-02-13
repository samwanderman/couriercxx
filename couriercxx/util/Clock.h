/*
 * Clock.h
 *
 *  Created on: 13.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_CLOCK_H_
#define COURIERCXX_UTIL_CLOCK_H_

#include <cstdint>

struct Time;

/**
 * Clock class
 */
class Clock {
public:
	/**
	 * Get current timstamp
	 *
	 * \return uint64_t timestamp in msec
	 */
	static uint64_t getTimestamp();

	/**
	 * Get current time
	 *
	 * \return Time
	 */
	static Time getTime();
};

#endif /* COURIERCXX_UTIL_CLOCK_H_ */
