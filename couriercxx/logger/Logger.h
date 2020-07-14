/*
 * Logger.h
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_LOGGER_LOGGER_H_
#define COURIERCXX_LOGGER_LOGGER_H_

#include <cstdio>
#include <string>

/**
 * Base logger class
 */
class Logger {
public:
	/**
	 * Log level
	 */
	static const uint8_t LEVEL_LOG;
	static const uint8_t LEVEL_INFO;
	static const uint8_t LEVEL_DEBUG;
	static const uint8_t LEVEL_WARNING;
	static const uint8_t LEVEL_ERROR;

	/**
	 * Empty constructor
	 */
	Logger();

	/**
	 * Default destructor
	 */
	virtual ~Logger();

	/**
	 * Set daemon mode
	 *
	 * \param[in] daemon - daemon mode
	 */
	void setDaemon(bool daemon);

	/**
	 * Use log file
	 */
	void useFile();

	/**
	 * Set app name for log
	 *
	 * \param[in] string name - name of application
	 */
	void setName(std::string name);

	/**
	 * Print string to log with level
	 *
	 * \param[in] level		- log level
	 * \param[in] format	- format string
	 * \param[in] args		- arguments for format string
	 */
	void print(uint8_t level, std::string format, va_list args);

private:
	std::string	name	= "";
	std::string logFile	= "";
	bool		daemon	= false;
	int			fd		= -1;

	/**
	 * Open log
	 */
	void open();

	/**
	 * Close log
	 */
	void close();
};

#endif /* COURIERCXX_LOGGER_LOGGER_H_ */
