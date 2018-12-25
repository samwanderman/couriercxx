/*
 * Log.h
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_LOGGER_LOG_H_
#define COURIERCXX_LOGGER_LOG_H_

#include <string>

class Logger;

/**
 * Simple logger class
 */
class Log {
public:
	/**
	 * Print info level log
	 *
	 * \param[in] string format - format string
	 * \param[in] any ... - arguments
	 */
	static void info(std::string format, ...);

	/**
	 * Print debug level log
	 *
	 * \param[in] string format - format string
	 * \param[in] any ... - arguments
	 */
	static void debug(std::string format, ...);

	/**
	 * Print error level log
	 *
	 * \param[in] string format - format string
	 * \param[in] any ... - arguments
	 */
	static void error(std::string format, ...);

	/**
	 * Print warning level log
	 *
	 * \param[in] string format - format string
	 * \param[in] any ... - arguments
	 */
	static void warn(std::string format, ...);

	/**
	 * Print log level log
	 *
	 * \param[in] string format - format string
	 * \param[in] any ... - arguments
	 */
	static void log(std::string format, ...);

	/**
	 * Set logger dameon-mode (all logs will be written in syslog)
	 *
	 * \param[in] bool daemon - true - set to daemon mode, false - set to common mode
	 */
	static void setDaemonMode(bool daemon);

	/**
	 * Set application name for logger
	 *
	 * \param[in] string name - app name
	 */
	static void setAppName(std::string name);

private:
	/**
	 * Get logger instance
	 */
	static Logger& getLog();
};

#endif /* COURIERCXX_LOGGER_LOG_H_ */
