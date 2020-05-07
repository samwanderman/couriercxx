/*
 * Request.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../../network/http/Request.h"

#include <event2/buffer.h>
#include <event2/buffer_compat.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <cstdarg>
#include <cstring>

namespace HTTP {

Request::Request(const evhttp_request* request) {
	this->request = request;
	inputBuffer = evhttp_request_get_input_buffer((evhttp_request*) request);
	outputBuffer = evhttp_request_get_output_buffer((evhttp_request*) request);
}

Request::~Request() { }

int Request::writeString(std::string format, ...) const {
	va_list args;
	va_start(args, format);
	evbuffer_add_vprintf((evbuffer*) outputBuffer, format.c_str(), args);
	va_end(args);

	return 0;
}

int Request::addResponseHeader(std::string name, std::string value) const {
	evhttp_add_header(request->output_headers, name.c_str(), value.c_str());

	return 0;
}

int Request::send(uint16_t code, std::string text) const {
	evhttp_send_reply((evhttp_request*) request, code, text.c_str(), (evbuffer*) outputBuffer);

	return 0;
}

int Request::getRAWInput(uint8_t* buffer, uint32_t bufferSize) const {
	uint8_t* dataRef = (uint8_t*) EVBUFFER_DATA((evbuffer*) inputBuffer);
	if (dataRef != nullptr) {
		uint32_t minSize = getInputBufferSize();
		minSize = minSize > bufferSize ? bufferSize : minSize;
		memmove(buffer, dataRef, bufferSize * sizeof(uint8_t));
		memset(&buffer[minSize], 0, bufferSize - minSize);

		return minSize;
	} else {
		return -1;
	}
}

const char* Request::getURI() const {
	return evhttp_request_get_uri(request);
};

uint32_t Request::getInputBufferSize() const {
	return evbuffer_get_length(inputBuffer);
}

};
