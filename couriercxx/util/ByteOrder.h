/*
 * ByteOrder.h
 *
 *  Created on: 28.05.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_BYTEORDER_H_
#define COURIERCXX_UTIL_BYTEORDER_H_

#include <cstdint>

/**
 * Class for byte order conversions
 */
class ByteOrder {
public:
	/**
	 * Convert from Big Endian bytes
	 *
	 * \param[in] uint8_t* bytes - pointer to bytes
	 *
	 * \return T - converted value
	 */
	template <typename T>
	static T fromBigEndian(const uint8_t* bytes);

	/**
	 * Convert from Little Endian bytes
	 *
	 * \param[in] uint8_t* bytes - pointer to bytes
	 *
	 * \return T - converted value
	 */
	template <typename T>
	static T fromLittleEndian(const uint8_t* bytes);

	/**
	 * Convert to Big Endian bytes
	 *
	 * \param[in] auto value - value
	 * \param[out] uint8_t* buffer - pointer to buffer
	 */
	template <typename T>
	static void toBigEndian(const T value, uint8_t* buffer);

	/**
	 * Convert to Little Endian bytes
	 *
	 * \param[in] auto value - value
	 * \param[out] uint8_t* buffer - pointer to buffer
	 */
	template <typename T>
	static void toLittleEndian(const T value, uint8_t* buffer);

	/**
	 * Convert to Little Endian bytes
	 *
	 * \param[in] auto value - value
	 * \param[in] uint16_t len - buffer length
	 * \param[out] uint8_t* buffer - pointer to buffer
	 */
	static void toLittleEndian(const uint8_t* value, uint16_t len, uint8_t* buffer);
};

#endif /* COURIERCXX_UTIL_BYTEORDER_H_ */
