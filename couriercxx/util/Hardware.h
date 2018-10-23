/*
 * Hardware.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_HARDWARE_H_
#define COURIERCXX_UTIL_HARDWARE_H_

/**
 * Class for hardware info
 */
class Hardware {
public:
	/**
	 * Get CPU temperature
	 *
	 * \return float - CPU temperature in Celsium
	 */
	static float getCPUTemperature();
};

#endif /* COURIERCXX_UTIL_HARDWARE_H_ */
