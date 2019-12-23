/*
 * SignalWatcher.h
 *
 *  Created on: 20.12.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_SIGNALWATCHER_H_
#define COURIERCXX_UTIL_SIGNALWATCHER_H_

/**
 * Signal watcher class
 */
class SignalWatcher {
public:
	static void set(void (*func) (int signal));
};

#endif /* COURIERCXX_UTIL_SIGNALWATCHER_H_ */
