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
#include <exception>

int System::startService(std::string name) {
	std::string cmd = "systemctl start ";
	cmd.append(name);

	return System::exec(cmd);
}

int System::stopService(std::string name) {
	std::string cmd = "systemctl stop ";
	cmd.append(name);

	return System::exec(cmd);
}

int System::restartService(std::string name) {
	std::string cmd = "systemctl restart ";
	cmd.append(name);

	return System::exec(cmd);
}

int System::restartNetwork() {
	return System::exec("systemctl restart networking");
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
	Log::debug("System.selfUpdate(%s)", path.c_str());

	if (fork() == 0) {
		std::string command = "dpkg -i ";
		command.append(path);
		//command.append(" &");

		System::exec(command);

		exit(0);
	}
}

std::string System::execAndGetOutput(std::string shellCommand) {
	std::string result = "";

	FILE* file = popen(shellCommand.c_str(), "r");
	if (file == nullptr) {
		return "ERROR";
	}

	try {
		uint8_t buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		while (fgets(reinterpret_cast<char*>(buffer), sizeof(buffer) - 1, file) != nullptr) {
			result += reinterpret_cast<char*>(buffer);

			memset(buffer, 0, sizeof(buffer));
		}
	} catch (...) {
		pclose(file);

		return "ERROR";
	}

	pclose(file);

	return result;
}

int System::exec(std::string shellCommand) {
	return system(shellCommand.c_str());
}
