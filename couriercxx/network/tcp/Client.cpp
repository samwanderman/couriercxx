/*
 * Client.cpp
 *
 *  Created on: 31.11.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Client.h"

#include <cstdint>
#include <atomic>

#include "../../util/System.h"

#ifndef _WIN32

#include <arpa/inet.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/thread.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <cstring>
#include <iterator>
#include <thread>

#include "../../logger/Log.h"

namespace TCP {

uint64_t totalRead = 0;

static void readCallback(struct bufferevent* buffEvent, void* ctx) {
	Log::debug("TCP.Client.readCallback()");

	Client* self = reinterpret_cast<Client*>(ctx);

	struct evbuffer *inputBuffer	= bufferevent_get_input(buffEvent);
	uint32_t		len				= evbuffer_get_length(inputBuffer);

	totalRead += len;

	std::vector<uint8_t> bytes(len);
	evbuffer_remove(inputBuffer, &bytes[0], len);

	self->addData(bytes);
}

static void eventCallback(struct bufferevent *buffEvent, short events, void *ctx) {
	Log::debug("TCP.Client.eventCallback()");

	if (events & BEV_EVENT_CONNECTED) {
		evutil_socket_t fd = bufferevent_getfd(buffEvent);
		int one = 1;
		setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
	} else if (events & BEV_EVENT_ERROR) {
		bufferevent_free(buffEvent);
	}
}

Client::Client(std::string ip, uint16_t port) {
	this->ip	= ip;
	this->port	= port;
}

Client::~Client() { }

int Client::open() {

#ifdef _WIN32

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		return -1;
	}

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_UNSPEC;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;

	struct addrinfo* result = nullptr;
	char portStr[16];
	memset(portStr, 0, 16);
	itoa(port, portStr, 10);
	if (getaddrinfo(ip.c_str(), portStr, &hints, &result) != 0) {
		WSACleanup();

		return -1;
	}

	struct addrinfo* ptr = nullptr;
	for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
		if ((socketFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET) {
			WSACleanup();

			return -1;
		}

		if (connect(socketFd, ptr->ai_addr, (int) ptr->ai_addrlen) == SOCKET_ERROR) {
			closesocket(socketFd);
			socketFd = INVALID_SOCKET;

			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (socketFd == INVALID_SOCKET) {
		WSACleanup();

		return -1;
	}

#else

	std::atomic<bool> ready;
	ready = false;

	auto func = [this, &ready]() {
		base = event_base_new();
		if (!base) {
			close();

			return;
		}

		struct sockaddr_in servAddr;
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(port);

		if (inet_pton(AF_INET, ip.c_str(), &servAddr.sin_addr) != 1) {
			close();

			return;
		}

		bufferEvent = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setcb(bufferEvent, readCallback, nullptr, eventCallback, this);
		bufferevent_enable(bufferEvent, EV_READ | EV_WRITE);

		if (bufferevent_socket_connect(bufferEvent,(struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
			Log::error("bufferevent_socket_connect() error");

			close();

			return;
		}

		ready = true;

		event_base_dispatch(base);
	};
	th = std::thread(func);

	while (!ready) {
		System::sleep(200);
	}

#endif

	opened = true;

	return 0;
}

int Client::close() {
#ifdef _WIN32

	closesocket(socketFd);
	socketFd = INVALID_SOCKET;
	WSACleanup();

#else

	opened = false;

	bytesVariable.notify_all();

	if (base != nullptr) {
		struct timeval time = { 0, 0 };
		event_base_loopexit(base, &time);
	}

	if (th.joinable()) {
		th.join();
	}

	if (bufferEvent != nullptr) {
		bufferevent_free(bufferEvent);
		bufferEvent = nullptr;
	}

#endif
	return 0;
}

int Client::write(const uint8_t* buffer, uint32_t bufferSize) {
	if (bufferSize == 0) {
		Log::warn("TCP.Client.write(): buffer size is 0");

		return 0;
	}

	std::lock_guard<decltype(writeMutex)> lock(writeMutex);

#ifdef _WIN32

	return send(socketFd, (const char*) buffer, bufferSize, 0);

#else

	if (evbuffer_add(bufferevent_get_output(bufferEvent), buffer, bufferSize) == -1) {
		return -1;
	}

#ifdef DEBUG
	Log::log("> ");
	for (uint32_t i = 0; i < bufferSize; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n");
#endif

	return bufferSize;

#endif

}

int Client::write(std::list<uint8_t>& buffer) {
	std::vector<uint8_t> vec(buffer.begin(), buffer.end());

	return write((const uint8_t*) &vec[0], vec.size());
}

int Client::read(uint8_t* buffer, uint32_t bufferSize) {
	Log::debug("Client.read()");

#ifdef _WIN32

	return recv(socketFd, (char*) buffer, bufferSize, 0);

#else

	std::unique_lock<decltype(bytesMutex)> lock(bytesMutex);

	while (bytes.size() == 0) {
		bytesVariable.wait(lock);

		if (!isOpen()) {
			return -1;
		}
	}

	uint32_t min = bufferSize < bytes.size() ? bufferSize: bytes.size();

	memmove(buffer, &bytes[0], min);
	bytes.erase(bytes.begin(), bytes.begin() + min);

#ifdef DEBUG
	Log::log("< ");
	for (uint32_t i = 0; i < min; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n");
#endif

	return min;

#endif

}

bool Client::isOpen() {
	return opened;
}

void Client::addData(std::vector<uint8_t>& data) {
	std::lock_guard<decltype(bytesMutex)> lock(bytesMutex);
	bytes.insert(bytes.end(), data.begin(), data.end());
	bytesVariable.notify_all();
}

} /* namespace TCP */

#endif
