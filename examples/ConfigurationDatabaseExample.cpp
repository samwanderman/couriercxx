/**
 * Example to demonstrate work with properties located in database
 */

#include <couriercxx/logger/Log.h>
#include <cstdint>
#include <cstring>

#include "../couriercxx/db/PostgresConnector.h"
#include "../couriercxx/property/Property.h"
#include "../couriercxx/property/PropertyDatabase.h"
#include "../couriercxx/property/PropertyFile.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	Log::info("App has started");

	if (ac < 2) {
		Log::info("Usage: %s [db|file]", &av[0][2]);

		return 0;
	}

	PostgresConnector* connector = nullptr;

	if (strncasecmp(av[1], "db", strlen("db")) == 0) {
		connector = new PostgresConnector("127.0.0.1", 5432, "ep2000", "ep2000", "ep2000", "UTF8");

		if (connector->open() == -1) {
			Log::error("PostgresConnector.open() error");

			delete connector;

			return -1;
		}
		Log::debug("PostgresConnector.open() success");

		if (Property::getInstance().init(new PropertyDatabase(connector)) == -1) {
			Log::error("Property.init() error");

			delete connector;

			return -1;
		}
	} else if (strncasecmp(av[1], "file", strlen("file")) == 0) {
		if (Property::getInstance().init(new PropertyFile("/etc/carddex/config")) == -1) {
			Log::error("Property.init() error");

			return -1;
		}
	} else {
		Log::info("Source %s not supported", av[1]);

		return 0;
	}

	// uint8_t test
	uint8_t* uint8tRes = Property::getUInt8("card.bytes");
	if (uint8tRes == nullptr) {
		Log::info("card.bytes is NULL");
	} else {
		Log::info("card.bytes is %u", *uint8tRes);
	}

	// int8_t test
//	int8_t* int8tRes = Property::get<int8_t>("card.bytes");
//	if (int8tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %i", *int8tRes);
//	}

	// uint16_t test
//	uint16_t* uint16tRes = Property::get<uint16_t>("card.bytes");
//	if (uint16tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %u", *uint16tRes);
//	}

	// int8_t test
//	int16_t* int16tRes = Property::get<int16_t>("card.bytes");
//	if (int16tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %i", *int16tRes);
//	}

	// uint32_t test
//	uint32_t* uint32tRes = Property::get<uint32_t>("card.bytes");
//	if (uint32tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %u", *uint32tRes);
//	}

	// int32_t test
//	int32_t* int32tRes = Property::get<int32_t>("card.bytes");
//	if (int32tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %i", *int32tRes);
//	}

	// uint64_t test
//	uint64_t* uint64tRes = Property::get<uint64_t>("card.bytes");
//	if (uint64tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %u", *uint64tRes);
//	}

	// int64_t test
//	int64_t* int64tRes = Property::get<int64_t>("card.bytes");
//	if (int64tRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %i", *int64tRes);
//	}

	// float test
//	float* floatRes = Property::get<float>("card.bytes");
//	if (floatRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %f", *floatRes);
//	}

	// double test
//	double* doubleRes = Property::get<double>("card.bytes");
//	if (doubleRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %f", *doubleRes);
//	}

	// string test
//	std::string* stringRes = Property::get<std::string>("card.bytes");
//	if (stringRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is '%s'", (*stringRes).c_str());
//	}

	// bool test
//	bool* boolRes = Property::get<bool>("card.bytes");
//	if (boolRes == nullptr) {
//		Log::info("card.bytes is NULL");
//	} else {
//		Log::info("card.bytes is %i", *boolRes);
//	}

	if (strncasecmp(av[1], "db", strlen("db")) == 0) {
		if (connector->close() == -1) {
			Log::error("PostgresConnector.close() error");
		} else {
			Log::debug("PostgresConnector.close() success");
		}

		delete connector;
	}

	Log::info("App has finished");

	return 0;
}
