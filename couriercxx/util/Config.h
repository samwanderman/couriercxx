/*
 * Config.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_CONFIG_H_
#define COURIERCXX_UTIL_CONFIG_H_

#include <string>

class ConfigBase;

/**
 * Read and load properties
 */
class Config {
public:
	/**
	 * Get property value by name
	 *
	 * <T> - property type
	 *
	 * \param[in] string propertyName - name of property
	 *
	 * \return <T> - property value
	 */
	template<typename T>
	static T get(std::string propertyName);

	/**
	 * Get instance of class
	 */
	static Config& getInstance();

	/**
	 * Init property file
	 */
	int init(std::string path);

private:
	ConfigBase* config = nullptr;

	Config();
	virtual ~Config();
};

#endif /* COURIERCXX_UTIL_CONFIG_H_ */
