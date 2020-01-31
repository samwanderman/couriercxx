/*
 * Clock.h
 *
 *  Created on: 13.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_CLOCK_H_
#define COURIERCXX_UTIL_CLOCK_H_

#include <cstdint>

/**
 * Base time struct
 */
struct Time {
	/**
	 * Constructor
	 */
	Time();

	/**
	 * Constructor
	 *
	 * \param[in] uint64_t timestamp - timestamp in msec
	 */
	Time(uint64_t timestamp);

	/**
	 * Milliseconds
	 */
	uint16_t msecond = 0;

	/**
	 * Seconds
	 */
	uint8_t second = 0;

	/**
	 * Minutes
	 */
	uint8_t minute = 0;

	/**
	 * Hours
	 */
	uint8_t hour = 0;

	/**
	 * Months
	 */
	uint8_t month = 0;

	/**
	 * Years
	 */
	uint16_t year = 0;

	/**
	 * Day o week
	 */
	uint8_t day = 0;

	/**
	 * Date
	 */
	uint8_t date = 0;

	/**
	 * GMT offset in hours
	 */
	int8_t gmt = 0;

	/**
	 * Get timestamp
	 *
	 * \return uint64_t - timestamp
	 */
	uint64_t getTimestamp();
};
typedef struct Time Time;

/**
 * System clock class
 */
class Clock {
public:
	/**
	 * Get current timestamp in milliseconds
	 *
	 * \return uint64_t timestamp in msec
	 */
	static uint64_t getTimestamp();

	/**
	 * Get current timestamp in microseconds
	 *
	 * \return uint64_t timestamp in microsec
	 */
	static uint64_t getTimestampExt();

	/**
	 * Get timezone offset in hours
	 *
	 * \return uint16_t timezone offset
	 */
	static uint16_t getTimezoneOffset();

	/**
	 * Get system time
	 *
	 * \return Time - system time in UTC
	 */
	static Time getTime();

	/**
	 * Set system time
	 *
	 * \param[in] Time time - time in UTC
	 */
	static void setTime(Time time);
};

#endif /* COURIERCXX_UTIL_CLOCK_H_ */
