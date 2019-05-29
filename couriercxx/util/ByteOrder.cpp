/*
 * ByteOrder.cpp
 *
 *  Created on: 28.05.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "ByteOrder.h"

#include <algorithm>
#include <cstring>

template <typename T>
T ByteOrder::fromBigEndian(const uint8_t* bytes) {
	T value = 0;
	uint16_t size = sizeof(T);

	for (uint16_t i = 0; i < size; i++) {
		value = (value << 8) | bytes[i];
	}

	return value;
}

template <typename T>
T ByteOrder::fromLittleEndian(const uint8_t* bytes) {
	T value = 0;
	uint16_t size = sizeof(T);

	for (uint16_t i = 0; i < size; i++) {
		value = (value << 8) | bytes[size - i - 1];
	}

	return value;
}

template <>
uint8_t* ByteOrder::fromLittleEndian(const uint8_t* bytes) {
	uint8_t* tmpBytes = (uint8_t*) bytes;

	std::reverse(&tmpBytes[0], &tmpBytes[4]);

	return tmpBytes;
}

template <typename T>
void ByteOrder::toBigEndian(const T value, uint8_t* buffer) {
	uint16_t size = sizeof(value);

	for (uint16_t i = 0; i < size; i++) {
		buffer[i] = (value >> ((size - i - 1) * 8)) & 0xff;
	}
}

template <typename T>
void ByteOrder::toLittleEndian(const T value, uint8_t* buffer) {
	uint16_t size = sizeof(value);

	for (uint16_t i = 0; i < size; i++) {
		buffer[i] = (value >> (i * 8)) & 0xff;
	}
}

void ByteOrder::toLittleEndian(const uint8_t* value, uint16_t len, uint8_t* buffer) {
	memmove(buffer, value, len * sizeof(uint8_t));
	std::reverse(buffer, &buffer[len]);
}

template int16_t ByteOrder::fromBigEndian<int16_t>(const uint8_t* bytes);
template int32_t ByteOrder::fromBigEndian<int32_t>(const uint8_t* bytes);
template int64_t ByteOrder::fromBigEndian<int64_t>(const uint8_t* bytes);
template uint16_t ByteOrder::fromBigEndian<uint16_t>(const uint8_t* bytes);
template uint32_t ByteOrder::fromBigEndian<uint32_t>(const uint8_t* bytes);
template uint64_t ByteOrder::fromBigEndian<uint64_t>(const uint8_t* bytes);
template int16_t ByteOrder::fromLittleEndian<int16_t>(const uint8_t* bytes);
template int32_t ByteOrder::fromLittleEndian<int32_t>(const uint8_t* bytes);
template int64_t ByteOrder::fromLittleEndian<int64_t>(const uint8_t* bytes);
template uint16_t ByteOrder::fromLittleEndian<uint16_t>(const uint8_t* bytes);
template uint32_t ByteOrder::fromLittleEndian<uint32_t>(const uint8_t* bytes);
template uint64_t ByteOrder::fromLittleEndian<uint64_t>(const uint8_t* bytes);
template void ByteOrder::toBigEndian<int16_t>(const int16_t value, uint8_t* bytes);
template void ByteOrder::toBigEndian<int32_t>(const int32_t value, uint8_t* bytes);
template void ByteOrder::toBigEndian<int64_t>(const int64_t value, uint8_t* bytes);
template void ByteOrder::toBigEndian<uint16_t>(const uint16_t value, uint8_t* bytes);
template void ByteOrder::toBigEndian<uint32_t>(const uint32_t value, uint8_t* bytes);
template void ByteOrder::toBigEndian<uint64_t>(const uint64_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<int16_t>(const int16_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<int32_t>(const int32_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<int64_t>(const int64_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<uint16_t>(const uint16_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<uint32_t>(const uint32_t value, uint8_t* bytes);
template void ByteOrder::toLittleEndian<uint64_t>(const uint64_t value, uint8_t* bytes);
