/*
 * IO.cpp
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IO.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

int IO::writeTo(std::string path, const uint8_t* buffer, uint32_t bufferSize) {
	int fd = ::open(path.c_str(), O_WRONLY | O_CREAT, 0200);
	if (fd == -1) {
		return -1;
	}

	int bytesWritten = ::write(fd, buffer, bufferSize);
	if (bytesWritten == -1) {
		::close(fd);

		return -1;
	}

	if (::close(fd) == -1) {
		return -1;
	}

	return bytesWritten;
}

int IO::readFrom(std::string path, uint8_t* buffer, uint32_t bufferSize) {
	int fd = ::open(path.c_str(), O_RDONLY);
	if (fd == -1) {
		return -1;
	}

	int bytesRead = ::read(fd, buffer, bufferSize);
	if (bytesRead == -1) {
		::close(fd);

		return -1;
	}

	if (::close(fd) == -1) {
		return -1;
	}

	return bytesRead;
}

bool IO::exists(std::string path) {
	struct stat buffer;
	return stat(path.c_str(), &buffer) == 0;
}

int IO::getSize(std::string path) {
	FILE* fd = fopen(path.c_str(), "r");
	if (fd == nullptr) {
		return -1;
	}

	int size = -1;

	fseek(fd, 0, SEEK_END);
	size = ftell(fd);


	if (fclose(fd) == -1) {
		return -1;
	}

	return size;
}

int IO::mkdir(std::string path) {
	char command[256];
	memset(command, 0, sizeof(command));
	snprintf(command, 255, "mkdir -p %s", path.c_str());

	return system(command);
}

int IO::rm(std::string path) {
	char command[256];
	memset(command, 0, sizeof(command));
	snprintf(command, 255, "rm -rf %s", path.c_str());

	return system(command);
}
