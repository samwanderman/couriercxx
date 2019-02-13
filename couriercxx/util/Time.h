/*
 * Time.h
 *
 *  Created on: Oct 22, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_TIME_H_
#define COURIERCXX_UTIL_TIME_H_

#include <cstdint>

/**
 * Time struct
 */
struct Time {
	/**
	 * Constructor
	 */
	Time();

	/**
	 * Constructor
	 *
	 * \param[in] uint64_t timestamp - unix timestamp
	 */
	Time(uint64_t timestamp);

	/**
	 *
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
	 * Get current data timestamp
	 *
	 * \return unix time timestamp
	 */
	uint64_t getTimestamp();
};
typedef struct Time Time;

#endif /* COURIERCXX_UTIL_TIME_H_ */
