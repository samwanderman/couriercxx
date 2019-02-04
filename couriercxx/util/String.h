/*
 * String.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_STRING_H_
#define COURIERCXX_UTIL_STRING_H_

#include <cstdint>
#include <list>
#include <string>

/**
 * Class for string operations
 */
class String {
public:
	/**
	 * Convert bytes data to ASCII HEX string
	 *
	 * \param[in] const uint8_t* hexData - byte buffer pointer
	 * \param[in] uint32_t hexDataLen - buffer len
	 * \param[out] uint8_t* asciiData - string buffer pointer
	 * \param[in] uint32_t asciiDataLen - string buffer max size
	 *
	 * \return int size of asciiData buffer
	 */
	static int hex2ascii(const uint8_t* hexData, uint32_t hexDataLen, uint8_t* asciiData, uint32_t asciiDataLen);

	/**
	 * Convert ASCII HEX string to byte data
	 *
	 * \param[in] const uint8_t* asciiData - string buffer pointer
	 * \param[in] uint32_t asciiDataLen - string buffer len
	 * \param[out] uint8_t* hexData - byte buffer pointer
	 * \param[in] uint32_t hexDataLen - byte buffer max size
	 *
	 * \return int size of hexData buffer
	 */
	static int ascii2hex(const uint8_t* asciiData, uint32_t asciiDataLen, uint8_t* hexData, uint32_t hexDataLen);

	/**
	 * Split string and return it's parts
	 *
	 * \param[in] string str - source string
	 * \param[in] string delim - delimeter string
	 *
	 * \return pars of splitted string
	 */
	static std::list<std::string> split(std::string str, std::string delim);
};

#endif /* COURIERCXX_UTIL_STRING_H_ */
