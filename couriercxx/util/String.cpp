/*
 * String.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "String.h"

#include <cstring>


uint8_t hex2asciiOne(uint8_t hex) {
	hex = hex & 0xf;
	return (hex < 0xa ? 0x30 : 0x37) + hex;
}

uint8_t ascii2hexOne(uint8_t ascii) {
	if ((ascii >= 0x61) && (ascii <= 0x66)) {
		return ascii - 0x61 + 0xa;
	} else if ((ascii >= 0x41) && (ascii <= 0x46)) {
		return ascii - 0x41 + 0xa;
	} else {
		return ascii - 0x30;
	}
}

int String::hex2ascii(const uint8_t* hexData, uint32_t hexDataLen, uint8_t* asciiData, uint32_t asciiDataLen) {
	if (hexDataLen * 2 > asciiDataLen) {
		return -1;
	}

	for (uint32_t i = 0; i < hexDataLen; i++) {
		asciiData[i * 2] = hex2asciiOne(hexData[i] >> 4);
		asciiData[i * 2 + 1] = hex2asciiOne(hexData[i]);
	}

	return hexDataLen * 2;
}

int String::ascii2hex(const uint8_t* asciiData, uint32_t asciiDataLen, uint8_t* hexData, uint32_t hexDataLen) {
	if (hexDataLen * 2 < asciiDataLen) {
		return -1;
	}

	for (uint32_t i = 0; i < hexDataLen; i++) {
		hexData[i] = (ascii2hexOne(asciiData[i * 2]) << 4 | ascii2hexOne(asciiData[i * 2 + 1]));
	}

	return hexDataLen;
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
