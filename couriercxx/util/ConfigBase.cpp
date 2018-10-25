/*
 * ConfigBase.cpp
 *
 *  Created on: Oct 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "ConfigBase.h"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <utility>


ConfigBase::ConfigBase(std::string path) {
	this->path = path;
}

ConfigBase::~ConfigBase() { }

int ConfigBase::read() {
	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		std::string line;

		while (getline(file, line)) {
			if (line.empty()) {
				continue;
			}

			std::regex expr("([0-9a-zA-Z+-\\._]*)=([0-9a-zA-Z+-\\._,!:\\s+\\/]*)");
			std::smatch res;

			if (std::regex_match(line, res, expr)) {
				if (res.size() == 3) {
					properties.insert(std::pair<std::string, std::string>(res[1].str(), res[2].str()));
				}
			}
		}

		file.close();

		return 0;
	}

	return -1;
}

int ConfigBase::write() {
	return 0;
}

int ConfigBase::set(std::string name, std::string value) {
	return 0;
}

template<typename T>
T ConfigBase::get(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return it->second;
	}

	throw std::invalid_argument("Not Found");
}

template<>
int ConfigBase::get<int>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return (int) strtoul(str, nullptr, 16);
		}

		return atoi(str);
	}

	throw std::invalid_argument("Not Found");
}

template<>
uint8_t ConfigBase::get<uint8_t>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return (uint8_t) strtoul(str, nullptr, 16);
		}

		return (uint8_t) atoi(str);
	}

	throw std::invalid_argument("Not Found");
}

template<>
uint16_t ConfigBase::get<uint16_t>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return (uint16_t) strtoul(str, nullptr, 16);
		}

		return (uint16_t) atoi(str);
	}

	throw std::invalid_argument("Not Found");
}

template<>
uint32_t ConfigBase::get<uint32_t>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return (uint32_t) strtoul(str, nullptr, 16);
		}

		return (uint32_t) atoi(str);
	}

	throw std::invalid_argument("Not Found");
}

template<>
uint64_t ConfigBase::get<uint64_t>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return (uint64_t) strtoul(str, nullptr, 16);
		}

		return (uint64_t) atol(str);
	}

	throw std::invalid_argument("Not Found");
}

template<>
float ConfigBase::get<float>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return atof(it->second.c_str());
	}

	throw std::invalid_argument("Not Found");
}

template<>
std::string ConfigBase::get<std::string>(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return it->second;
	}

	throw std::invalid_argument("Not Found");
}

