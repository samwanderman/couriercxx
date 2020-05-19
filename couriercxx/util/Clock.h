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
	 * \param[in] timestamp - timestamp in msec
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
	 * \return timestamp
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
	 * \return timestamp in msec
	 */
	static uint64_t getTimestamp();

	/**
	 * Get current timestamp in microseconds
	 *
	 * \return timestamp in microsec
	 */
	static uint64_t getTimestampExt();

	/**
	 * Get timezone offset in hours
	 *
	 * \return timezone offset
	 */
	static int32_t getTimezoneOffset();

	/**
	 * Get minutes from timestamp
	 *
	 * \return minutes from day start
	 */
	static int32_t getDayMinutesFromTimestamp(uint64_t timestamp);

	/**
	 * Get system time
	 *
	 * \return system time in UTC
	 */
	static Time getTime();

	/**
	 * Set system time
	 *
	 * \param[in] time - time in UTC
	 */
	static void setTime(Time time);

	/**
	 * Set system time
	 *
	 * \param[in] time		- time in UTC
	 * \param[in] timezone	- timezone
	 */
	static void setTime(Time time, int32_t timezone);
};

#endif /* COURIERCXX_UTIL_CLOCK_H_ */
