/*
 * System.h
 *
 *  Created on: 14.02.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_SYSTEM_H_
#define COURIERCXX_UTIL_SYSTEM_H_

#include <cstdint>
#include <string>

/**
 * Class for system features
 */
class System {
public:
	/**
	 * Start service
	 *
	 * \param[in] string name - service name
	 *
	 * \return 0 if success, -1 if error
	 */
	static int startService(std::string name);

	/**
	 * Stop service
	 *
	 * \param[in] string name - service name
	 *
	 * \return 0 if success, -1 if error
	 */
	static int stopService(std::string name);

	/**
	 * Restart service
	 *
	 * \param[in] string name - service name
	 *
	 * \return 0 if success, -1 if error
	 */
	static int restartService(std::string name);

	/**
	 * Restart network
	 *
	 * \return 0 if success, -1 if error
	 */
	static int restartNetwork();

	/**
	 * Reboot system
	 *
	 * \return 0 if success, -1 if error
	 */
	static int reboot();

	/**
	 * Sleep for milliseconds
	 *
	 * \param[in] uint64_t milliseconds
	 */
	static void sleep(uint64_t milliseconds);

	/**
	 * Sleep for microseconds
	 *
	 * \param[in] uint64_t microseconds
	 */
	static void usleep(uint64_t microseconds);

	/**
	 * Make directory
	 *
	 * \param[in] string path - path
	 *
	 * \return int - 0 if success, -1 if error
	 */
	static int mkdir(std::string path);
};

#endif /* COURIERCXX_UTIL_SYSTEM_H_ */
