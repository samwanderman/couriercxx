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
	 * \param[in] path			- path to file
	 * \param[in] buffer		- pointer to buffer
	 * \param[in] bufferSize	- size of buffer
	 *
	 * \return
	 * 			- number of written bytes if success
	 * 			- -1 if error
	 */
	static int writeTo(std::string path, const uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Read data from file
	 *
	 * \param[in]	path		- path to file
	 * \param[out]	buffer		- pointer to buffer
	 * \param[in]	bufferSize	- size of buffer
	 *
	 * \return
	 * 			- number of read bytes if success
	 * 			- -1 if error
	 */
	static int readFrom(std::string path, uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Copy file
	 *
	 * \param[in] src - source file
	 * \param[in] dst - destination file
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 */
	static int copyFile(std::string src, std::string dst);

	/**
	 * Check if file exists
	 *
	 * \param[in] path - path to file
	 *
	 * \return
	 * 			- true	- file exists
	 * 			- false - file not exists
	 */
	static bool exists(std::string path);

	/**
	 * Get file size
	 *
	 * \param[in] path - path to file
	 *
	 * \return
	 * 			- size of file if success
	 * 			- -1 if error
	 */
	static int getSize(std::string path);

	/**
	 * Make new directory
	 *
	 * \param[in] path - path to directory
	 *
	 * \return
	 * 			0	- if success
	 * 			-1	- if error
	 */
	static int mkdir(std::string path);

	/**
	 * Remove directory or file
	 *
	 * \param[in] path - path to delete
	 *
	 * \return
	 * 			0 	- if success
	 * 			-1	- if error
	 */
	static int rm(std::string path);
};

#endif /* COURIERCXX_UTIL_IO_H_ */
