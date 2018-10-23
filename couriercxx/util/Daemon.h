/*
 * Daemon.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_DAEMON_H_
#define COURIERCXX_UTIL_DAEMON_H_

/**
 * Daemonizer class
 */
class Daemon {
public:
	/**
	 * Daemonize process
	 */
	static void daemonize();
};

#endif /* COURIERCXX_UTIL_DAEMON_H_ */
