/*
 * String.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "String.h"

#include <cstring>
#include <vector>

uint8_t writeASCII(uint8_t hex) {
	hex = hex & 0xf;
	return (hex < 0xa ? 0x30 : 0x37) + hex;
}

uint8_t readASCII(uint8_t ascii) {
	if ((ascii >= 0x61) && (ascii <= 0x66)) {
		return ascii - 0x61 + 0xa;
	} else if ((ascii >= 0x41) && (ascii <= 0x46)) {
		return ascii - 0x41 + 0xa;
	} else {
		return ascii - 0x30;
	}
}

int String::writeUInt8(uint8_t value, uint8_t* buffer, uint32_t pos) {
	buffer[pos] = value;

	return sizeof(value);
}

int String::writeInt8(int8_t value, uint8_t* buffer, uint32_t pos) {
	buffer[pos++] = (uint8_t) value;

	return sizeof(value);
}

int String::writeUInt16BE(uint16_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt16BE(int16_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeUInt16LE(uint16_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt16LE(int16_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeUInt32BE(uint32_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt32BE(int32_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeUInt32LE(uint32_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt32LE(int32_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeUInt64BE(uint64_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt64BE(int64_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeUInt64LE(uint64_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeInt64LE(int64_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i < sizeof(value); i++) {
		buffer[pos++] = (uint8_t) ((value >> (i * 8)) & 0xff);
	}

	return sizeof(value);
}

int String::writeString(std::string str, uint8_t* buffer, uint32_t pos) {
	std::vector<uint8_t> data(str.begin(), str.end());

	uint32_t i = 0;
	for (; i < data.size(); i++) {
		buffer[pos + i] = data[i];
	}

	buffer[pos + i] = 0;

	return i;
}

int String::writeUInt8ASCII(uint8_t value, uint8_t* buffer, uint32_t pos) {
	buffer[pos++] = writeASCII(value >> 4);
	buffer[pos++] = writeASCII(value & 0xf);

	return sizeof(value) * 2;
}

int String::writeInt8ASCII(int8_t value, uint8_t* buffer, uint32_t pos) {
	buffer[pos++] = writeASCII((uint8_t) value >> 4);
	buffer[pos++] = writeASCII((uint8_t) value & 0xf);

	return sizeof(value) * 2;
}

int String::writeUInt16BEASCII(uint16_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt16BEASCII(int16_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeUInt16LEASCII(uint16_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt16LEASCII(int16_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeUInt32BEASCII(uint32_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt32BEASCII(int32_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeUInt32LEASCII(uint32_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt32LEASCII(int32_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeUInt64BEASCII(uint64_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt64BEASCII(int64_t value, uint8_t* buffer, uint32_t pos) {
	for (int64_t i = sizeof(value) - 1; i >= 0; i--) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeUInt64LEASCII(uint64_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

int String::writeInt64LEASCII(int64_t value, uint8_t* buffer, uint32_t pos) {
	for (uint32_t i = 0; i <= sizeof(value); i++) {
		pos += writeUInt8ASCII((uint8_t) (value >> (i * 8)), buffer, pos);
	}

	return sizeof(value) * 2;
}

uint8_t String::readUInt8(const uint8_t* buffer, uint32_t pos) {
	return buffer[pos];
}

int8_t String::readInt8(const uint8_t* buffer, uint32_t pos) {
	return (int8_t) buffer[pos];
}

uint16_t String::readUInt16BE(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return value;
}

int16_t String::readInt16BE(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return (int16_t) value;
}

uint16_t String::readUInt16LE(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint16_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return value;
}

int16_t String::readInt16LE(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint16_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return (int16_t) value;
}

uint32_t String::readUInt32BE(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return value;
}

int32_t String::readInt32BE(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return (int32_t) value;
}

uint32_t String::readUInt32LE(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint32_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return value;
}

int32_t String::readInt32LE(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint32_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return (int32_t) value;
}

uint64_t String::readUInt64BE(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return value;
}

int64_t String::readInt64BE(const uint8_t* buffer, uint32_t pos) {
	int64_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | buffer[pos++];
	}

	return value;
}

uint64_t String::readUInt64LE(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint64_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return value;
}

int64_t String::readInt64LE(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;
	for (uint32_t i = 0; i < sizeof(value); i++) {
		uint64_t tmp = buffer[pos++];
		value = value | (tmp << (i * 8));
	}

	return (int64_t) value;
}

std::string String::readString(const uint8_t* buffer, uint32_t pos) {
	std::string str;
	uint32_t i = 0;

	while (buffer[pos + i] != 0) {
		str.push_back(buffer[pos + i]);

		i++;
	}

	return str;
}

uint8_t String::readUInt8ASCII(const uint8_t* buffer, uint32_t pos) {
	return (readASCII(buffer[pos]) << 4) | readASCII(buffer[pos + 1]);
}

int8_t String::readInt8ASCII(const uint8_t* buffer, uint32_t pos) {
	return (int8_t) ((readASCII(buffer[pos]) << 4) | readASCII(buffer[pos + 1]));
}

uint16_t String::readUInt16BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int16_t String::readInt16BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int16_t) value;
}

uint16_t String::readUInt16LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int16_t String::readInt16LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint16_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int16_t) value;
}

uint32_t String::readUInt32BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int32_t String::readInt32BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int32_t) value;
}

uint32_t String::readUInt32LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int32_t String::readInt32LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint32_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int32_t) value;
}

uint64_t String::readUInt64BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int64_t String::readInt64BEASCII(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;

	for (uint32_t i = 0; i < sizeof(value); i++) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int64_t) value;
}

uint64_t String::readUInt64LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return value;
}

int64_t String::readInt64LEASCII(const uint8_t* buffer, uint32_t pos) {
	uint64_t value = 0;

	for (uint32_t i = sizeof(value) - 1; i >= 0; i--) {
		value = (value << 8) | readUInt8ASCII(buffer, pos + i * 2);
	}

	return (int64_t) value;
}

int String::writeBufferASCII(const uint8_t* hexData, uint32_t hexDataSize, uint8_t* asciiData, uint32_t asciiDataSize) {
	if (hexDataSize * 2 > asciiDataSize) {
		return -1;
	}

	for (uint32_t i = 0; i < hexDataSize; i++) {
		asciiData[i * 2]		= writeASCII(hexData[i] >> 4);
		asciiData[i * 2 + 1]	= writeASCII(hexData[i]);
	}

	return hexDataSize * 2;
}

int String::readBufferASCII(const uint8_t* asciiData, uint32_t asciiDataSize, uint8_t* hexData, uint32_t hexDataSize) {
	if (hexDataSize * 2 < asciiDataSize) {
		return -1;
	}

	for (uint32_t i = 0; i < hexDataSize; i++) {
		hexData[i] = (readASCII(asciiData[i * 2]) << 4 | readASCII(asciiData[i * 2 + 1]));
	}

	return hexDataSize;
}

std::string& String::trimLeft(std::string& str, std::string& delim) {
	str.erase(0, str.find_last_of(delim) + 1);

	return str;
}

std::string& String::trimRight(std::string& str, std::string& delim) {
	str.erase(str.find_last_of(delim) + 1, str.size());

	return str;
}

std::list<std::string> String::split(std::string str, std::string delim) {
	std::list<std::string> parts;

	char* srcStr = (char*) str.c_str(), *token = strtok(srcStr, delim.c_str());

	while (token != nullptr) {
		parts.push_back(std::string(token));
		token = strtok(nullptr, delim.c_str());
	}

	return parts;
}
