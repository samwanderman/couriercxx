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
	 * Write uint8_t value to buffer
	 *
	 * \param[in] uint8_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt8(uint8_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int8_t value to buffer
	 *
	 * \param[in] int8_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt8(int8_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint16_t BIG ENDIAN value to buffer
	 *
	 * \param[in] uint16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt16BE(uint16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int16_t BIG ENDIAN value to buffer
	 *
	 * \param[in] int16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt16BE(int16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint16_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] uint16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt16LE(uint16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int16_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] int16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt16LE(int16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint32_t BIG ENDIAN value to buffer
	 *
	 * \param[in] uint32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt32BE(uint32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int32_t BIG ENDIAN value to buffer
	 *
	 * \param[in] int32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt32BE(int32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint32_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] uint32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt32LE(uint32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int32_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] int32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt32LE(int32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint64_t BIG ENDIAN value to buffer
	 *
	 * \param[in] uint64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt64BE(uint64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int64_t BIG ENDIAN value to buffer
	 *
	 * \param[in] int64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt64BE(int64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint64_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] uint64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt64LE(uint64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int64_t LITTLE ENDIAN value to buffer
	 *
	 * \param[in] int64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt64LE(int64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint8_t value to buffer in ascii
	 *
	 * \param[in] uint8_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt8ASCII(uint8_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int8_t value to buffer in ascii
	 *
	 * \param[in] int8_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt8ASCII(int8_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint16_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt16BEASCII(uint16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int16_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] int16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt16BEASCII(int16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint16_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt16LEASCII(uint16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int16_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] int16_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt16LEASCII(int16_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint32_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt32BEASCII(uint32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int32_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] int32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt32BEASCII(int32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint32_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt32LEASCII(uint32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int32_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] int32_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt32LEASCII(int32_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint64_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt64BEASCII(uint64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int64_t BIG ENDIAN value to buffer in ascii
	 *
	 * \param[in] int64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt64BEASCII(int64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write uint64_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] uint64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeUInt64LEASCII(uint64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Write int64_t LITTLE ENDIAN value to buffer in ascii
	 *
	 * \param[in] int64_t value - value
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - position to write
	 *
	 * \return int - number of written bytes
	 */
	static int writeInt64LEASCII(int64_t value, uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint8_t value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint8_t value
	 */
	static uint8_t readUInt8(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint8_t value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int8_t value
	 */
	static int8_t readInt8(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint16_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint16_t value
	 */
	static uint16_t readUInt16BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int16_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int16_t value
	 */
	static int16_t readInt16BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint16_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint16_t value
	 */
	static uint16_t readUInt16LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int16_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int16_t value
	 */
	static int16_t readInt16LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint32_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint32_t value
	 */
	static uint32_t readUInt32BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int16_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int32_t value
	 */
	static int32_t readInt32BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint32_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint32_t value
	 */
	static uint32_t readUInt32LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int32_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int32_t value
	 */
	static int32_t readInt32LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint64_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint64_t value
	 */
	static uint64_t readUInt64BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int64_t BIG ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int64_t value
	 */
	static int64_t readInt64BE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint64_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint64_t value
	 */
	static uint64_t readUInt64LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int64_t LITTLE ENDIAN value from buffer
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int64_t value
	 */
	static int64_t readInt64LE(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint8_t value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint8_t value
	 */
	static uint8_t readUInt8ASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int8_t value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int8_t value
	 */
	static int8_t readInt8ASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint16_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint16_t value
	 */
	static uint16_t readUInt16BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int16_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int16_t value
	 */
	static int16_t readInt16BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint16_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint16_t value
	 */
	static uint16_t readUInt16LEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int16_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int16_t value
	 */
	static int16_t readInt16LEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint32_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint32_t value
	 */
	static uint32_t readUInt32BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int32_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int32_t value
	 */
	static int32_t readInt32BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint32_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint32_t value
	 */
	static uint32_t readUInt32LEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int32_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int32_t value
	 */
	static int32_t readInt32LEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint64_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint64_t value
	 */
	static uint64_t readUInt64BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int64_t BIG ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int64_t value
	 */
	static int64_t readInt64BEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read uint64_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return uint64_t value
	 */
	static uint64_t readUInt64LEASCII(const uint8_t* buffer, uint32_t pos);

	/**
	 * Read int64_t LITTLE ENDIAN value from buffer from ascii
	 *
	 * \param[in] const uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t pos - read start position
	 *
	 * \return int64_t value
	 */
	static int64_t readInt64LEASCII(const uint8_t* buffer, uint32_t pos);

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
