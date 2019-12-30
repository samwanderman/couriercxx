/*
 * PropertyDatabase.cpp
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "PropertyDatabase.h"

#ifdef _WIN32
#else
#include <pqxx/pqxx>
#endif

#include <exception>
#include <list>
#include <typeindex>

#include "../logger/Log.h"
#include "../db/PostgresConnector.h"
#include "../db/Value.h"

PropertyDatabase::PropertyDatabase(PostgresConnector* connector) : IProperty() {
	this->connector = connector;
}

PropertyDatabase::~PropertyDatabase() { }

int PropertyDatabase::open() {
	if (!connector->isOpen()) {
		return -1;
	}

	std::list<std::type_index> types;
	types.clear();
	types.push_back(DB::typeString);
	connector->addStatement("getParamValue", "SELECT value FROM PARAMS WHERE name = $1", types);


	types.clear();
	types.push_back(DB::typeString);
	types.push_back(DB::typeString);
	connector->addStatement("setParamValue", "UPDATE PARAMS SET value = $2 WHERE name = $1 ", types);

	return 0;
}

int PropertyDatabase::close() {
	connector->removeStatement("getParamValue");
	connector->removeStatement("setParamValue");

	return 0;
}

uint8_t* PropertyDatabase::getUInt8(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new uint8_t(result[0]["value"].as<uint16_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setUInt8(std::string propertyName, uint8_t value) {
	setString(propertyName, std::to_string(value));
}

int8_t* PropertyDatabase::getInt8(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new int8_t(result[0]["value"].as<int16_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setInt8(std::string propertyName, int8_t value) {
	setString(propertyName, std::to_string(value));
}

uint16_t* PropertyDatabase::getUInt16(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new uint16_t(result[0]["value"].as<uint16_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setUInt16(std::string propertyName, uint16_t value) {
	setString(propertyName, std::to_string(value));
}

int16_t* PropertyDatabase::getInt16(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new int16_t(result[0]["value"].as<int16_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setInt16(std::string propertyName, int16_t value) {
	setString(propertyName, std::to_string(value));
}

uint32_t* PropertyDatabase::getUInt32(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new uint32_t(result[0]["value"].as<uint32_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setUInt32(std::string propertyName, uint32_t value) {
	setString(propertyName, std::to_string(value));
}

int32_t* PropertyDatabase::getInt32(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new int32_t(result[0]["value"].as<int32_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setInt32(std::string propertyName, int32_t value) {
	setString(propertyName, std::to_string(value));
}

uint64_t* PropertyDatabase::getUInt64(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new uint64_t(result[0]["value"].as<uint64_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setUInt64(std::string propertyName, uint64_t value) {
	setString(propertyName, std::to_string(value));
}

int64_t* PropertyDatabase::getInt64(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new int64_t(result[0]["value"].as<int64_t>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setInt64(std::string propertyName, int64_t value) {
	setString(propertyName, std::to_string(value));
}

float* PropertyDatabase::getFloat(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new float(result[0]["value"].as<float>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setFloat(std::string propertyName, float value) {
	setString(propertyName, std::to_string(value));
}

double* PropertyDatabase::getDouble(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new double(result[0]["value"].as<double>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setDouble(std::string propertyName, double value) {
	setString(propertyName, std::to_string(value));
}

std::string* PropertyDatabase::getString(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new std::string(result[0]["value"].as<const char*>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif

	return nullptr;
}

void PropertyDatabase::setString(std::string propertyName, std::string value) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		const char* propValue = value.c_str();
		pqxx::result result = connector->execStatement("setParamValue", DB::StringValue(&propName), DB::StringValue(&propValue));
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif
}

bool* PropertyDatabase::getBool(std::string propertyName) {
#ifdef _WIN32
#else
	try {
		const char* propName = propertyName.c_str();
		pqxx::result result = connector->execStatement("getParamValue", DB::StringValue(&propName));

		if (result.size() > 0) {
			if (!result[0]["value"].is_null()) {
				return new bool(result[0]["value"].as<bool>());
			}
		}
	} catch (const std::exception& exception) {
		Log::error("%s", exception.what());
	}
#endif
	return nullptr;
}

void PropertyDatabase::setBool(std::string propertyName, bool value) {
	setString(propertyName, std::to_string(value));
}
