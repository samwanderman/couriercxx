/*
 * HTTPTest.cpp
 *
 *  Created on: 07.05.2020
 *      Author: Potapov Sergei
 *       Email: potapov.sa@carddex.ru
 */

#include <couriercxx/logger/Log.h>
#include <couriercxx/util/String.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/http.h>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Bcrypt.lib")
#pragma comment(lib, "event.lib")
#endif

static void requestDone(struct evhttp_request *req, void *ctx) {
	if (!req || !evhttp_request_get_response_code(req)) {
		Log::error("Some error occured");

		return;
	}

	Log::debug("Response: %d %s", evhttp_request_get_response_code(req), evhttp_request_get_response_code_line(req));
//
//	uint8_t buffer[256];
//	int nread = -1;
//
//	while ((nread = evbuffer_remove(evhttp_request_get_input_buffer(req), buffer, sizeof(buffer) - 1)) > 0) {
//		Log::debug("%i", nread);
//
//		for (int i = 0; i < nread; i++) {
//			Log::log("%c", buffer[i]);
//		}
//	}
}

int main(int ac, char** av) {
	Log::debug("HTTP PAYLOAD TEST");

	if (ac < 4) {
		Log::info("Usage:\r\n$ %s host port file", av[0]);

		return 0;
	}

	std::vector<uint8_t> buffer;

	std::ifstream file(av[3], std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		uint32_t size = file.tellg();
		buffer.resize(size);
		file.seekg(0, std::ios::beg);
		file.read((char*) &buffer[0], size);
		file.close();
	}

	const char*	host	= av[1];
	uint32_t	port	= atoi(av[2]);

	struct event_base* eventBase = event_base_new();
	if (eventBase == nullptr) {
		Log::error("event_base_new() error");

		return -1;
	}

	struct bufferevent* bufferEvent = bufferevent_socket_new(eventBase, -1, BEV_OPT_CLOSE_ON_FREE);
	if (bufferEvent == nullptr) {
		Log::error("bufferevent_socket_new() error");

		event_base_free(eventBase);

		return -1;
	}

	struct evhttp_connection *evcon = evhttp_connection_base_bufferevent_new(eventBase, nullptr, bufferEvent, host, port);
	if (evcon == nullptr) {
		Log::error("evhttp_connection_base_bufferevent_new() error");

		bufferevent_free(bufferEvent);

		event_base_free(eventBase);

		return -1;
	}

	struct evhttp_request* req = evhttp_request_new(requestDone, bufferEvent);
	if (req == nullptr) {
		Log::error("evhttp_request_new() error");

		evhttp_connection_free(evcon);

		bufferevent_free(bufferEvent);

		event_base_free(eventBase);

		return -1;
	}

	struct evkeyvalq*	output_headers = evhttp_request_get_output_headers(req);
	evhttp_add_header(output_headers, "Host", host);
	evhttp_add_header(output_headers, "Connection", "close");

	std::string str(av[3]), delim = "/";
	std::string trimFileName = String::trimLeft(str, delim);

	struct evbuffer*	output_buffer = evhttp_request_get_output_buffer(req);
	evbuffer_add(output_buffer, trimFileName.c_str(), trimFileName.size());
	uint8_t zero = 0;
	evbuffer_add(output_buffer, &zero, 1);
	evbuffer_add(output_buffer, &buffer[0], buffer.size());

	evhttp_add_header(output_headers, "Content-Length", std::to_string(buffer.size() + trimFileName.size() + 1).c_str());

	std::string uri = "/update";
	Log::debug("URI is '%s'", uri.c_str());

	int result = evhttp_make_request(evcon, req, EVHTTP_REQ_POST, uri.c_str());
	if (result != 0) {
		Log::error("evhttp_make_request() error");
	}

	event_base_dispatch(eventBase);

	evhttp_connection_free(evcon);

	bufferevent_free(bufferEvent);

	event_base_free(eventBase);

	return 0;
}
