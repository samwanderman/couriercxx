/*
 * Daemon.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Daemon.h"

#include "../logger/Log.h"

#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

void Daemon::daemonize() {
#ifndef _WIN32
	int pid = fork();
	if (pid == -1) {
		exit(EXIT_SUCCESS);
	} else if (pid != 0) {
		exit(EXIT_SUCCESS);
	} else {
		umask(0);
		setsid();
		const char* dir = "/";
		if (chdir(dir) == -1) {
			Log::error("Can't change dir to '%s'", dir);
		}
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
#endif
}
