/*
 * SignalWatcher.cpp
 *
 *  Created on: 20.12.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SignalWatcher.h"

#include <csignal>
#include <cstring>

void SignalWatcher::set(void (*func) (int signal)) {
#ifdef _WIN32
	std::signal(SIGINT, func);
	std::signal(SIGTERM, func);
	std::signal(SIGSEGV, func);
#else
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = func;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGSEGV);
	act.sa_mask = set;
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGINT, &act, 0);
	sigaction(SIGHUP, &act, 0);
	sigaction(SIGSEGV, &act, 0);
#endif
}
