/*
 * Logger.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Logger.h"

#include <syslog.h>
#include <cstdint>
#include <cstring>

// color macrosses
#define COLOR_ERROR		"\x1b[31m"
#define COLOR_LOG		"\x1b[32m"
#define COLOR_DEBUG		"\x1b[30;1m"
#define COLOR_WARNING	"\x1b[93m"
#define COLOR_RESET		"\x1b[0m"

#define STRING_MAX_LEN	1024

Logger::Logger() {
	open();
}

Logger::~Logger() {
	close();
}

void Logger::open() {
	if (daemon) {
		openlog(name.c_str(), 0, LOG_USER);
	}
}

void Logger::close() {
	if (daemon) {
		closelog();
	}
}

void Logger::setDaemon(bool daemon) {
	this->daemon = daemon;
	close();
	open();
}

void Logger::setName(std::string name) {
	this->name = name;
}

void Logger::print(uint8_t level, std::string format, va_list args) {
	if (daemon) {
		int logLevel = LOG_INFO;

		switch (level) {
		case LEVEL_ERROR:
			logLevel = LOG_ERR;

			break;

		case LEVEL_DEBUG:
			logLevel = LOG_DEBUG;

			break;

		case LEVEL_WARNING:
			logLevel = LOG_WARNING;

			break;

		case LEVEL_INFO:
			logLevel = LOG_INFO;

			break;

		default:
			break;
		}

		char bytes[STRING_MAX_LEN];
		memset(bytes, 0, STRING_MAX_LEN);
		vsnprintf(bytes, STRING_MAX_LEN - 1, format.c_str(), args);
		syslog(logLevel, bytes);
	} else {
		std::string logLevel = "[INFO]";

		switch (level) {
		case LEVEL_ERROR:
			logLevel = "[ERROR]";

			break;

		case LEVEL_DEBUG:
			logLevel = "[DEBUG]";

			break;

		case LEVEL_WARNING:
			logLevel = "[WARNING]";

			break;

		case LEVEL_INFO:
			logLevel = "[INFO]";

			break;

		default:
			break;
		}

		char bytes[STRING_MAX_LEN];
		memset(bytes, 0, STRING_MAX_LEN);
		vsnprintf(bytes, STRING_MAX_LEN - 1, format.c_str(), args);

		switch (level) {
		case LEVEL_ERROR:
			printf(COLOR_ERROR "%s: %s: %s" COLOR_RESET "\r\n", name.c_str(), logLevel.c_str(), bytes);

			break;

		case LEVEL_DEBUG:
			printf(COLOR_DEBUG "%s: %s: %s" COLOR_RESET "\r\n", name.c_str(), logLevel.c_str(), bytes);

			break;

		case LEVEL_WARNING:
			printf(COLOR_WARNING "%s: %s: %s" COLOR_RESET "\r\n", name.c_str(), logLevel.c_str(), bytes);

			break;

		case LEVEL_INFO:
			printf(COLOR_LOG "%s: %s: %s" COLOR_RESET "\r\n", name.c_str(), logLevel.c_str(), bytes);

			break;

		default:
			printf("%s", bytes);

			break;
		}
	}
}
