/*
 * Log.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Log.h"

#include <cstdarg>

#include "Logger.h"

void Log::info(std::string format, ...) {
	va_list args;
	va_start(args, format);
	Log::getLog().print(Logger::LEVEL_INFO, format, args);
	va_end(args);
}

void Log::debug(std::string format, ...) {
	va_list args;
	va_start(args, format);
	Log::getLog().print(Logger::LEVEL_DEBUG, format, args);
	va_end(args);
}

void Log::warn(std::string format, ...) {
	va_list args;
	va_start(args, format);
	Log::getLog().print(Logger::LEVEL_WARNING, format, args);
	va_end(args);
}

void Log::error(std::string format, ...) {
	va_list args;
	va_start(args, format);
	Log::getLog().print(Logger::LEVEL_ERROR, format, args);
	va_end(args);
}

void Log::log(std::string format, ...) {
	va_list args;
	va_start(args, format);
	Log::getLog().print(Logger::LEVEL_LOG, format, args);
	va_end(args);
}

void Log::setDaemonMode(bool daemon) {
	Log::getLog().setDaemon(daemon);
}

void Log::setAppName(std::string name) {
	Log::getLog().setName(name);
}

Logger& Log::getLog() {
	static Logger logger;
	return logger;
}
