/*
 * Request.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Request.h"

#include <event2/buffer.h>
#include <event2/buffer_compat.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <cstdarg>
#include <cstring>

Request::Request(evhttp_request *request) {
	this->request = request;
	inputBuffer = evhttp_request_get_input_buffer(request);
	outputBuffer = evhttp_request_get_output_buffer(request);
}

Request::~Request() {
	if (request != nullptr) {
		delete request;
		request = nullptr;
	}

	if (inputBuffer != nullptr) {
		inputBuffer = nullptr;
	}

	if (outputBuffer != nullptr) {
		outputBuffer = nullptr;
	}
}

int Request::writeString(std::string format, ...) {
	va_list args;
	va_start(args, format);
	evbuffer_add_vprintf(outputBuffer, format.c_str(), args);
	va_end(args);

	return 0;
}

int Request::addResponseHeader(std::string name, std::string value) {
	evhttp_add_header(request->output_headers, name.c_str(), value.c_str());

	return 0;
}

int Request::send(uint16_t code, std::string text) {
	evhttp_send_reply(request, code, text.c_str(), outputBuffer);

	return 0;
}

int Request::getRAWInput(uint8_t* buffer, uint32_t bufferSize) {
	uint8_t* dataRef = (uint8_t*) EVBUFFER_DATA(inputBuffer);
	uint16_t minSize = evbuffer_get_length(inputBuffer);
	minSize = minSize > bufferSize ? bufferSize : minSize;
	memmove(buffer, dataRef, bufferSize * sizeof(uint8_t));
	memset(&buffer[minSize], 0, bufferSize - minSize);

	return minSize;
}
