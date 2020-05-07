/*
 * Request.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_HTTP_REQUEST_H_
#define COURIERCXX_NETWORK_HTTP_REQUEST_H_

#include <cstdint>
#include <string>

struct evhttp_request;
struct evbuffer;

namespace HTTP {

/**
 * Request wrapper
 */
class Request {
public:
	/**
	 * Constructor
	 *
	 * \param[in] request - initial request
	 */
	Request(const evhttp_request *request);

	/**
	 * Destructor
	 */
	virtual ~Request();

	Request(const Request& other) = default;
	Request(Request&& other) = default;
	Request& operator=(const Request& other) = default;
	Request& operator=(Request&& other) = default;

	/**
	 * Write string to output
	 *
	 * \param[in] string format - format string
	 * \params...
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int writeString(std::string format, ...) const;

	/**
	 * Add header to response
	 *
	 * \param[in] string name - name of header
	 * \param[in] string value - value of header
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int addResponseHeader(std::string name, std::string value) const;

	/**
	 * Send code to client
	 *
	 * \param[in] uint16_t code - code
	 * \param[in] string text - additional text
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int send(uint16_t code, std::string text) const;

	/**
	 * Get raw input
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max size of buffer
	 */
	virtual int getRAWInput(uint8_t* buffer, uint32_t bufferSize) const;

	/**
	 * Get uri
	 *
	 * \return uri
	 */
	const char* getURI() const;

	/**
	 * Get input buffer size
	 *
	 * \return input buffer size
	 */
	uint32_t getInputBufferSize() const;

private:
	const evhttp_request *request = nullptr;
	const struct evbuffer* outputBuffer = nullptr;
	const struct evbuffer* inputBuffer = nullptr;
};

};

#endif /* COURIERCXX_NETWORK_HTTP_REQUEST_H_ */
