/*
 * System.h
 *
 *  Created on: 14.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_SYSTEM_H_
#define COURIERCXX_UTIL_SYSTEM_H_

#include <cstdint>
#include <exception>
#include <string>

/**
 * Class for system features
 */
class System {
public:
	/**
	 * Start service
	 *
	 * \param[in] name - service name
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 */
	static int startService(std::string name);

	/**
	 * Stop service
	 *
	 * \param[in] name - service name
	 *
	 * \return
	 *			- 0 if success
	 *			- -1 if error
	 */
	static int stopService(std::string name);

	/**
	 * Restart service
	 *
	 * \param[in] name - service name
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 */
	static int restartService(std::string name);

	/**
	 * Restart network
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 */
	static int restartNetwork();

	/**
	 * Reboot system
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
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
	 * Self update
	 *
	 * \param[in] path - path to DEB packet
	 */
	static void selfUpdate(std::string path);

	/**
	 * Daemonize process
	 */
	static void daemonize();

	/**
	 * Set global exception handler
	 *
	 * \param[in] handler - exception handler
	 */
	static void setGlobalExceptionHandler(std::terminate_handler handler);

	/**
	 * Make process singletone
	 *
	 * \param[in] name - process uid
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 * 			- 1 if another proccess is running
	 *
	 * NOTE:
	 *   app should has root permission
	 */
	static int singleton(std::string uid);

	/**
	 * Release singleton
	 *
	 * \param[in] name - process uid
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 * 			- 1 if another proccess is running
	 *
	 * NOTE:
	 * 	 app should has root permission
	 */
	static int releaseSingleton(std::string uid);

	/**
	 * Execute shell command and return result
	 *
	 * \param shellCommand - command to execute
	 *
	 * \return result
	 */
	static std::string execAndGetOutput(std::string shellCommand);

	/**
	 * Execute shell command and return status
	 *
	 * \param[in] shellCommand - command to execute
	 *
	 * \return status
	 */
	static int exec(std::string shellCommand);
};

#endif /* COURIERCXX_UTIL_SYSTEM_H_ */
