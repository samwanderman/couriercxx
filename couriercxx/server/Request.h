/*
 * Request.h
 *
 *  Created on: Oct 18, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_SERVER_REQUEST_H_
#define COURIERCXX_SERVER_REQUEST_H_

#include <cstdint>
#include <string>

struct evhttp_request;
struct evbuffer;

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

	/**
	 * Write string to output
	 *
	 * \param[in] string format - format string
	 * \params...
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int writeString(std::string format, ...);

	/**
	 * Add header to response
	 *
	 * \param[in] string name - name of header
	 * \param[in] string value - value of header
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int addResponseHeader(std::string name, std::string value);

	/**
	 * Send code to client
	 *
	 * \param[in] uint16_t code - code
	 * \param[in] string text - additional text
	 *
	 * \return 0 if success, -1 if error
	 */
	virtual int send(uint16_t code, std::string text);

	/**
	 * Get raw input
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max size of buffer
	 */
	virtual int getRAWInput(uint8_t* buffer, uint32_t bufferSize);

private:
	const evhttp_request *request = nullptr;
	const struct evbuffer* outputBuffer = nullptr;
	const struct evbuffer* inputBuffer = nullptr;
};

#endif /* COURIERCXX_SERVER_REQUEST_H_ */
