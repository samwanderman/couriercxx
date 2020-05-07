/*
 * System.cpp
 *
 *  Created on: 14.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "System.h"

#include <cstdint>
#include <fcntl.h>
#include <cerrno>

#include "../logger/Log.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/reboot.h>
#endif
#include <chrono>
#include <cstdio>
#include <cstring>
#include <thread>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <cstdlib>

int System::startService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl start %s", name.c_str());

	return system(command);
}

int System::stopService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl stop %s", name.c_str());

	return system(command);
}

int System::restartService(std::string name) {
	char command[64];
	memset(command, 0, sizeof(command));
	snprintf(command, 63, "systemctl restart %s", name.c_str());

	return system(command);
}

int System::restartNetwork() {
	return system("systemctl restart networking");
}

int System::reboot() {
#ifndef _WIN32
	return ::reboot(RB_AUTOBOOT);
#else
	return 0;
#endif
}

void System::sleep(uint64_t milliseconds) {
	usleep(milliseconds * 1000);
}

void System::usleep(uint64_t microseconds) {
#ifdef _WIN32
	Sleep(microseconds/ 1000);
#else
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
#endif
}

void System::daemonize() {
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

void System::setGlobalExceptionHandler(std::terminate_handler t) {
	std::set_terminate(t);
}

int System::singleton(std::string uid) {
#ifdef _WIN32
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, uid.c_str());
    if (!hMutex) {
    	hMutex = CreateMutex(0, 0, uid.c_str());
    	if (hMutex) {
    		return 0;
    	}
    }

    return -1;
#else
	std::string path = "/var/run/" + uid;
	int pidFile = ::open(path.c_str(), O_CREAT | O_RDWR, 0666);
	if (pidFile == -1) {
		return -1;
	}

	if (flock(pidFile, LOCK_EX | LOCK_NB) != -1) {
		return 0;
	} else {
		if (errno == EWOULDBLOCK) {
			return 1;
		}
	}
#endif

	return -1;
}

int System::releaseSingleton(std::string uid) {
#ifdef _WIN32
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, uid.c_str());
    if (!hMutex) {
    	ReleaseMutex(hMutex);

    	return 0;
    }

    return -1;
#else
    return 0;
#endif
}

void System::selfUpdate(std::string path) {
	char command[256];
	memset(command, 0, sizeof(command));
	snprintf(command, 255, "dpkg -i %s &", path.c_str());

	system(command);
}
