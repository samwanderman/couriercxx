/*
 * Config.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Config.h"

#include <cstdint>
#include <exception>
#include <map>
#include <utility>

#include "../logger/Log.h"
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

int Config::update() {
	return getInstance().config->read();
}

int Config::save() {
	return getInstance().config->write();
}

Config& Config::getInstance() {
	static Config config;

	return config;
}

void Config::set(std::string name, std::string value) {
	getInstance().config->getProperties().erase(name);
	getInstance().config->getProperties().insert(std::pair<std::string, std::string>(name, value));
}

template<typename T>
T Config::get(std::string propertyName) {
	return getInstance().config->get<T>(propertyName);
}

template<typename T>
T Config::getIfExists(std::string propertyName, T defaultValue) {
	return getInstance().config->getIfExists<T>(propertyName, defaultValue);
}

template<>
int Config::get<int>(std::string propertyName) {
	return getInstance().config->get<int>(propertyName);
}

template<>
int Config::getIfExists<int>(std::string propertyName, int defaultValue) {
	return getInstance().config->getIfExists<int>(propertyName, defaultValue);
}

template<>
bool Config::get<bool>(std::string propertyName) {
	return getInstance().config->get<bool>(propertyName);
}

template<>
bool Config::getIfExists<bool>(std::string propertyName, bool defaultValue) {
	return getInstance().config->getIfExists<bool>(propertyName, defaultValue);
}

template<>
uint8_t Config::get<uint8_t>(std::string propertyName) {
	return getInstance().config->get<uint8_t>(propertyName);
}

template<>
uint8_t Config::getIfExists<uint8_t>(std::string propertyName, uint8_t defaultValue) {
	return getInstance().config->getIfExists<uint8_t>(propertyName, defaultValue);
}

template<>
uint16_t Config::get<uint16_t>(std::string propertyName) {
	return getInstance().config->get<uint16_t>(propertyName);
}

template<>
uint16_t Config::getIfExists<uint16_t>(std::string propertyName, uint16_t defaultValue) {
	return getInstance().config->getIfExists<uint16_t>(propertyName, defaultValue);
}

template<>
uint32_t Config::get<uint32_t>(std::string propertyName) {
	return getInstance().config->get<uint32_t>(propertyName);
}

template<>
uint32_t Config::getIfExists<uint32_t>(std::string propertyName, uint32_t defaultValue) {
	return getInstance().config->getIfExists<uint32_t>(propertyName, defaultValue);
}

template<>
uint64_t Config::get<uint64_t>(std::string propertyName) {
	return getInstance().config->get<uint64_t>(propertyName);
}

template<>
uint64_t Config::getIfExists<uint64_t>(std::string propertyName, uint64_t defaultValue) {
	return getInstance().config->getIfExists<uint64_t>(propertyName, defaultValue);
}

template<>
float Config::get<float>(std::string propertyName) {
	return getInstance().config->get<float>(propertyName);
}

template<>
float Config::getIfExists<float>(std::string propertyName, float defaultValue) {
	return getInstance().config->getIfExists<float>(propertyName, defaultValue);
}

template<>
std::string Config::get<std::string>(std::string propertyName) {
	return getInstance().config->get<std::string>(propertyName);
}

template<>
std::string Config::getIfExists(std::string propertyName, std::string defaultValue) {
	return getInstance().config->getIfExists<std::string>(propertyName, defaultValue);
}
