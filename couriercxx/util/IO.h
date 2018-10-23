/*
 * IO.h
 *
 *  Created on: Sep 27, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_IO_H_
#define COURIERCXX_UTIL_IO_H_

#include <cstdint>
#include <string>

/**
 * Simple class for IO operations
 */
class IO {
public:
	/**
	 * Write data to file
	 *
	 * \param[in] string path - path to file
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of written bytes if success, -1 if error
	 */
	static int writeTo(std::string path, const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from file
	 *
	 * \param[in] string path - path to file
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - size of buffer
	 *
	 * \return number of read bytes if success, -1 if error
	 */
	static int readFrom(std::string path, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Check if file exists
	 *
	 * \param[in] string path - path to file
	 *
	 * \return true - file exists, false - file not exists
	 */
	static bool exists(std::string path);
};

#endif /* COURIERCXX_UTIL_IO_H_ */
