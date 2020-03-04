/*
 * Property.cpp
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "Property.h"

#include "IProperty.h"

Property::Property() { }

Property::~Property() { }

int Property::init(IProperty* property) {
	if (this->property != nullptr) {
		delete this->property;
		this->property = nullptr;
	}

	this->property = property;

	return this->property->open();
}

int Property::destroy() {
	if (property != nullptr) {
		property->close();
		delete property;
		property = nullptr;
	}

	return 0;
}

Property& Property::getInstance() {
	static Property property;

	return property;
}

// uint8_t
uint8_t* Property::getUInt8(std::string propertyName) {
	return getInstance().property->getUInt8(propertyName);
}

uint8_t Property::getUInt8(std::string propertyName, uint8_t defaultValue) {
	return getInstance().property->getUInt8(propertyName, defaultValue);
}

void Property::setUInt8(std::string propertyName, uint8_t value) {
	return getInstance().property->setUInt8(propertyName, value);
}

// int8_t
int8_t* Property::getInt8(std::string propertyName) {
	return getInstance().property->getInt8(propertyName);
}

int8_t Property::getInt8(std::string propertyName, int8_t defaultValue) {
	return getInstance().property->getInt8(propertyName, defaultValue);
}

void Property::setInt8(std::string propertyName, int8_t value) {
	return getInstance().property->setInt8(propertyName, value);
}

// uint16_t
uint16_t* Property::getUInt16(std::string propertyName) {
	return getInstance().property->getUInt16(propertyName);
}

uint16_t Property::getUInt16(std::string propertyName, uint16_t defaultValue) {
	return getInstance().property->getUInt16(propertyName, defaultValue);
}

void Property::setUInt16(std::string propertyName, uint16_t value) {
	return getInstance().property->setUInt16(propertyName, value);
}

// int16_t
int16_t* Property::getInt16(std::string propertyName) {
	return getInstance().property->getInt16(propertyName);
}

int16_t Property::getInt16(std::string propertyName, int16_t defaultValue) {
	return getInstance().property->getInt16(propertyName, defaultValue);
}

void Property::setInt16(std::string propertyName, int16_t value) {
	return getInstance().property->setInt16(propertyName, value);
}

// uint32_t
uint32_t* Property::getUInt32(std::string propertyName) {
	return getInstance().property->getUInt32(propertyName);
}

uint32_t Property::getUInt32(std::string propertyName, uint32_t defaultValue) {
	return getInstance().property->getUInt32(propertyName, defaultValue);
}

void Property::setUInt32(std::string propertyName, uint32_t value) {
	return getInstance().property->setUInt32(propertyName, value);
}

// int32_t
int32_t* Property::getInt32(std::string propertyName) {
	return getInstance().property->getInt32(propertyName);
}

int32_t Property::getInt32(std::string propertyName, int32_t defaultValue) {
	return getInstance().property->getInt32(propertyName, defaultValue);
}

void Property::setInt32(std::string propertyName, int32_t value) {
	return getInstance().property->setInt32(propertyName, value);
}

// uint64_t
uint64_t* Property::getUInt64(std::string propertyName) {
	return getInstance().property->getUInt64(propertyName);
}

uint64_t Property::getUInt64(std::string propertyName, uint64_t defaultValue) {
	return getInstance().property->getUInt64(propertyName, defaultValue);
}

void Property::setUInt64(std::string propertyName, uint64_t value) {
	return getInstance().property->setUInt64(propertyName, value);
}

// int64_t
int64_t* Property::getInt64(std::string propertyName) {
	return getInstance().property->getInt64(propertyName);
}

int64_t Property::getInt64(std::string propertyName, int64_t defaultValue) {
	return getInstance().property->getInt64(propertyName, defaultValue);
}

void Property::setInt64(std::string propertyName, int64_t value) {
	return getInstance().property->setInt64(propertyName, value);
}

// float
float* Property::getFloat(std::string propertyName) {
	return getInstance().property->getFloat(propertyName);
}

float Property::getFloat(std::string propertyName, float defaultValue) {
	return getInstance().property->getFloat(propertyName, defaultValue);
}

void Property::setFloat(std::string propertyName, float value) {
	return getInstance().property->setFloat(propertyName, value);
}

// double
double* Property::getDouble(std::string propertyName) {
	return getInstance().property->getDouble(propertyName);
}

double Property::getDouble(std::string propertyName, double defaultValue) {
	return getInstance().property->getDouble(propertyName, defaultValue);
}

void Property::setDouble(std::string propertyName, double value) {
	return getInstance().property->setUInt8(propertyName, value);
}

// string
std::string* Property::getString(std::string propertyName) {
	return getInstance().property->getString(propertyName);
}

std::string Property::getString(std::string propertyName, std::string defaultValue) {
	return getInstance().property->getString(propertyName, defaultValue);
}

void Property::setString(std::string propertyName, std::string value) {
	return getInstance().property->setString(propertyName, value);
}

// bool
bool* Property::getBool(std::string propertyName) {
	return getInstance().property->getBool(propertyName);
}

bool Property::getBool(std::string propertyName, bool defaultValue) {
	return getInstance().property->getBool(propertyName, defaultValue);
}

void Property::setBool(std::string propertyName, bool value) {
	return getInstance().property->setBool(propertyName, value);
}
