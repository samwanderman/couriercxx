/*
 * Config.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Config.h"

#include <cstdint>

#include "ConfigBase.h"

Config::Config() { }

Config::~Config() {
	if (config == nullptr) {
		delete config;
		config = nullptr;
	}
}

int Config::init(std::string path) {
	if (config == nullptr) {
		delete config;
		config = nullptr;
	}

	config = new ConfigBase(path);

	return config->read();
}

Config& Config::getInstance() {
	static Config config;

	return config;
}

template<typename T>
T Config::get(std::string propertyName) {
	return getInstance().config->get<T>(propertyName);
}

template<>
int Config::get<int>(std::string propertyName) {
	return getInstance().config->get<int>(propertyName);
}

template<>
uint8_t Config::get<uint8_t>(std::string propertyName) {
	return getInstance().config->get<uint8_t>(propertyName);
}

template<>
uint16_t Config::get<uint16_t>(std::string propertyName) {
	return getInstance().config->get<uint16_t>(propertyName);
}

template<>
uint32_t Config::get<uint32_t>(std::string propertyName) {
	return getInstance().config->get<uint32_t>(propertyName);
}

template<>
uint64_t Config::get<uint64_t>(std::string propertyName) {
	return getInstance().config->get<uint64_t>(propertyName);
}

template<>
float Config::get<float>(std::string propertyName) {
	return getInstance().config->get<float>(propertyName);
}

template<>
std::string Config::get<std::string>(std::string propertyName) {
	return getInstance().config->get<std::string>(propertyName);
}
