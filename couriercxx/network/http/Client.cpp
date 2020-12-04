/*
 * Client.cpp
 *
 *  Created on: 07.05.2020
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Client.h"

#include <cstdint>
#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/util.h>
#include <string>
#include <thread>
#include <future>
#include <list>

#include "../../logger/Log.h"

#define BUFFER_SIZE	1024

namespace HTTP {

void onRequestDone(struct evhttp_request* request, void* arg){
	Client* client = reinterpret_cast<Client*>(arg);

	if ((request == nullptr) || (request->response_code != 200)) {
		Log::error("HTTP.Client.onRequestDone() error");

		client->getCallback()(true, nullptr, 0);

		return;
	}

	Log::debug("HTTP.Client.onRequestDone([%i]) success", request->response_code);

    uint8_t buffer[BUFFER_SIZE];
    int size = evbuffer_remove(request->input_buffer, &buffer, sizeof(buffer) - 1);
    buffer[size] = 0;

    client->getCallback()(false, buffer, size);
}

Client::Client(ClientConfig config, ClientCallback callback) {
	Log::debug("HTTP.Client()");
	this->config	= config;
	this->callback	= callback;
}

Client::~Client() {
	Log::debug("~HTTP.Client()");
}

int Client::start() {
	Log::debug("HTTP.Client.start()");

	if (running) {
		return -1;
	}

	running = true;

	base = event_base_new();
	if (base == nullptr) {
		Log::error("event_base_new() error");

		return -1;
	}
	Log::debug("event_base_new() success");

	Log::debug("Host: %s, Port: %u", config.host.c_str(), config.port);
	conn = evhttp_connection_base_new(base, nullptr, config.host.c_str(), config.port);
	if (conn == nullptr) {
		Log::error("evhttp_connection_base_new() error");

		return -1;
	}
	Log::debug("evhttp_connection_base_new() success");

	return 0;
}

int Client::stop() {
	Log::debug("HTTP.Client.stop()");

	if (!running) {
		return -1;
	}

	running = false;

	clean();

	return 0;
}

std::promise<Client::Response> Client::send(HTTP::Method method, std::string url, uint8_t* data = nullptr, uint32_t dataSize = 0) {
	Log::debug("HTTP.Client.send('%s')", url.c_str());

	std::promise<Response> p;

	// if client not running - exit
	if (!running) {
		p.set_value(Response(0));

		return p;
	}

	auto req = evhttp_request_new(/*onRequestDone*/[](struct evhttp_request* request, void* arg){
		std::promise<Response>* p = reinterpret_cast<std::promise<Response>*>(arg);

		Response response;

		if ((request == nullptr) || (request->response_code != 200)) {
			Log::error("HTTP.Client.onRequestDone() error");

			response.status = 0;

			p->set_value(response);

			return;
		}

		Log::debug("HTTP.Client.onRequestDone([%i]) success", request->response_code);

	    int bufferLen = evbuffer_get_length(request->input_buffer);
	    response.status = 200;
	    response.data.resize(bufferLen + 1);

	    evbuffer_remove(request->input_buffer, &response.data[0], bufferLen);
	    response.data[bufferLen] = 0;

	    p->set_value(response);
	}, &p);
	evhttp_add_header(req->output_headers, "Host", config.host.c_str());

	switch (method) {
	case HTTP::Method::Get: {
	    evhttp_make_request(conn, req, EVHTTP_REQ_GET, url.c_str());
	} break;

	case HTTP::Method::Post: {
		auto outputBuffer = evhttp_request_get_output_buffer(req);
		evbuffer_add(outputBuffer, data, dataSize);
		evutil_snprintf(reinterpret_cast<char*>(data), sizeof(data) - 1, "%lu", (unsigned long) dataSize);
		evhttp_add_header(req->output_headers, "Content-Length", std::to_string(dataSize).c_str());
	    evhttp_make_request(conn, req, EVHTTP_REQ_POST, url.c_str());
	} break;

	default:
		p.set_value(Response(0));

		return p;
	}

	evhttp_connection_set_timeout(req->evcon, config.timeout / 1000);

	std::thread th([this]() {
		event_base_dispatch(base);
	});
	th.detach();

	return p;
}

void Client::clean() {
	Log::debug("HTTP.Client.clean()");

	if (event_base_loopbreak(base) != 0) {
		Log::error("event_base_loopbreak() error");

		return;
	}
	Log::debug("event_base_loopbreak() success");

	if (conn != nullptr) {
		evhttp_connection_free(conn);
		conn = nullptr;
	}

	if (base != nullptr) {
		event_base_free(base);
		base = nullptr;
	}
}

ClientCallback Client::getCallback() {
	return callback;
}

};
