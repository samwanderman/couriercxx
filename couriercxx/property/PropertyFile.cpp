/*
 * PropertyFile.cpp
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "PropertyFile.h"

#include <cstdlib>
#include <fstream>
#include <regex>
#include <utility>

PropertyFile::PropertyFile(std::string path) : IProperty() {
	this->path = path;
}

PropertyFile::~PropertyFile() { }

int PropertyFile::open() {
	return load();
}

int PropertyFile::close() {
	properties.clear();

	return 0;
}

int PropertyFile::save() {
	std::ofstream file(path, std::ios::out | std::ios::binary);

	if (file.is_open()) {
		std::map<std::string, std::string>::iterator it = properties.begin();

		while (it != properties.end()) {
			std::string line = it->first + "=" + it->second;

			file << line << std::endl;

			it++;
		}

		file.close();
	}

	return 0;
}

int PropertyFile::load() {
	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (file.is_open()) {
		std::string line;
		properties.clear();

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

uint8_t* PropertyFile::getUInt8(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new uint8_t(strtoul(str, nullptr, 16));
		}

		return new uint8_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setUInt8(std::string paramName, uint8_t value) {
	setString(paramName, std::to_string(value));
}

int8_t* PropertyFile::getInt8(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new int8_t(strtoul(str, nullptr, 16));
		}

		return new int8_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setInt8(std::string paramName, int8_t value) {
	setString(paramName, std::to_string(value));
}

uint16_t* PropertyFile::getUInt16(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new uint16_t(strtoul(str, nullptr, 16));
		}

		return new uint16_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setUInt16(std::string paramName, uint16_t value) {
	setString(paramName, std::to_string(value));
}

int16_t* PropertyFile::getInt16(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new int16_t(strtoul(str, nullptr, 16));
		}

		return new int16_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setInt16(std::string paramName, int16_t value) {
	setString(paramName, std::to_string(value));
}

uint32_t* PropertyFile::getUInt32(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new uint32_t(strtoul(str, nullptr, 16));
		}

		return new uint32_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setUInt32(std::string paramName, uint32_t value) {
	setString(paramName, std::to_string(value));
}

int32_t* PropertyFile::getInt32(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new int32_t(strtoul(str, nullptr, 16));
		}

		return new int32_t(atoi(str));
	}

	return nullptr;
}

void PropertyFile::setInt32(std::string paramName, int32_t value) {
	setString(paramName, std::to_string(value));
}

uint64_t* PropertyFile::getUInt64(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new uint64_t(strtoul(str, nullptr, 16));
		}

		return new uint64_t(atol(str));
	}

	return nullptr;
}

void PropertyFile::setUInt64(std::string paramName, uint64_t value) {
	setString(paramName, std::to_string(value));
}

int64_t* PropertyFile::getInt64(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		const char* str = it->second.c_str();

		if ((str[0] == '0') && ((str[1] == 'x') || (str[1] == 'X'))) {
			return new int64_t(strtoul(str, nullptr, 16));
		}

		return new int64_t(atol(str));
	}

	return nullptr;
}

void PropertyFile::setInt64(std::string paramName, int64_t value) {
	setString(paramName, std::to_string(value));
}

float* PropertyFile::getFloat(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return new float(atof(it->second.c_str()));
	}

	return nullptr;
}

void PropertyFile::setFloat(std::string paramName, float value) {
	setString(paramName, std::to_string(value));
}

double* PropertyFile::getDouble(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return new double(atof(it->second.c_str()));
	}

	return nullptr;
}

void PropertyFile::setDouble(std::string paramName, double value) {
	setString(paramName, std::to_string(value));
}

bool* PropertyFile::getBool(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return new bool(atoi(it->second.c_str()));
	}

	return nullptr;
}

void PropertyFile::setBool(std::string paramName, bool value) {
	setString(paramName, std::to_string(value));
}

std::string* PropertyFile::getString(std::string propertyName) {
	std::map<std::string, std::string>::iterator it = properties.find(propertyName);
	if (it != properties.end()) {
		return new std::string(it->second);
	}

	return nullptr;
}

void PropertyFile::setString(std::string name, std::string value) {
	properties.erase(name);
	properties.insert(std::pair<std::string, std::string>(name, value));
	save();
}
