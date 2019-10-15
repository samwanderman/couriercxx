/*
 * IProperty.cpp
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "IProperty.h"

IProperty::IProperty() { }

IProperty::~IProperty() { }

int IProperty::open() {
	return 0;
}

int IProperty::close() {
	return 0;
}

uint8_t* IProperty::getUInt8(std::string paramName) {
	return nullptr;
}

uint8_t IProperty::getUInt8(std::string paramName, uint8_t defaultValue) {
	uint8_t* res = getUInt8(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setUInt8(std::string paramName, uint8_t value) { }

int8_t* IProperty::getInt8(std::string paramName) {
	return nullptr;
}

int8_t IProperty::getInt8(std::string paramName, int8_t defaultValue) {
	int8_t* res = getInt8(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setInt8(std::string paramName, int8_t value) { }

uint16_t* IProperty::getUInt16(std::string paramName) {
	return nullptr;
}

uint16_t IProperty::getUInt16(std::string paramName, uint16_t defaultValue) {
	uint16_t* res = getUInt16(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setUInt16(std::string paramName, uint16_t value) { }

int16_t* IProperty::getInt16(std::string paramName) {
	return nullptr;
}

int16_t IProperty::getInt16(std::string paramName, int16_t defaultValue) {
	int16_t* res = getInt16(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setInt16(std::string paramName, int16_t value) { }

uint32_t* IProperty::getUInt32(std::string paramName) {
	return nullptr;
}

uint32_t IProperty::getUInt32(std::string paramName, uint32_t defaultValue) {
	uint32_t* res = getUInt32(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setUInt32(std::string paramName, uint32_t value) { }

int32_t* IProperty::getInt32(std::string paramName) {
	return nullptr;
}

int32_t IProperty::getInt32(std::string paramName, int32_t defaultValue) {
	int32_t* res = getInt32(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setInt32(std::string paramName, int32_t value) { }

uint64_t* IProperty::getUInt64(std::string paramName) {
	return nullptr;
}

uint64_t IProperty::getUInt64(std::string paramName, uint64_t defaultValue) {
	uint64_t* res = getUInt64(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setUInt64(std::string paramName, uint64_t value) { }

int64_t* IProperty::getInt64(std::string paramName) {
	return nullptr;
}

int64_t IProperty::getInt64(std::string paramName, int64_t defaultValue) {
	int64_t* res = getInt64(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setInt64(std::string paramName, int64_t value) { }

float* IProperty::getFloat(std::string paramName) {
	return nullptr;
}

float IProperty::getFloat(std::string paramName, float defaultValue) {
	float* res = getFloat(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setFloat(std::string paramName, float value) { }

double* IProperty::getDouble(std::string paramName) {
	return nullptr;
}

double IProperty::getDouble(std::string paramName, double defaultValue) {
	double* res = getDouble(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setDouble(std::string paramName, double value) { }

std::string* IProperty::getString(std::string paramName) {
	return nullptr;
}

std::string IProperty::getString(std::string paramName, std::string defaultValue) {
	std::string* res = getString(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setString(std::string paramName, std::string value) { }

bool* IProperty::getBool(std::string paramName) {
	return nullptr;
}

bool IProperty::getBool(std::string paramName, bool defaultValue) {
	bool* res = getBool(paramName);
	if (res == nullptr) {
		return defaultValue;
	}

	defaultValue = *res;
	delete res;

	return defaultValue;
}

void IProperty::setBool(std::string paramName, bool value) { }
