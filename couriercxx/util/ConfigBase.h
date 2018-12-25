/*
 * ConfigBase.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_CONFIGBASE_H_
#define COURIERCXX_UTIL_CONFIGBASE_H_

#include <map>
#include <string>

/**
 * Base configuration operation
 */
class ConfigBase {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string path - path to configuration
	 */
	ConfigBase(std::string path);

	/**
	 * Destructor
	 */
	virtual ~ConfigBase();

	/**
	 * Read configuration file
	 *
	 * \return 0 if success, -1 if error
	 */
	int read();

	/**
	 * Write configuration file
	 *
	 * \return 0 if success, -1 if error
	 */
	int write();

	/**
	 * Get property value by name
	 *
	 * <T> - property type
	 *
	 * \param[in] string name - property name
	 *
	 * \return <T> - property value
	 */
	template<typename T>
	T get(std::string name);

	/**
	 * Get all properties
	 *
	 * \return map of properties
	 */
	std::map<std::string, std::string>& getProperties();

	/**
	 * Set all properties
	 *
	 * \param[in] map<string, string> properties - properties
	 *
	 * \return 0 if success, -1 if error
	 */
	int setProperties(std::map<std::string, std::string> properties);

	/**
	 * Set property
	 *
	 * \param[in] string name - property name
	 * \param[in] string value - property value
	 */
	int set(std::string name, std::string value);

private:
	std::string path = "";
	std::map<std::string, std::string> properties;
};

#endif /* COURIERCXX_UTIL_CONFIGBASE_H_ */
