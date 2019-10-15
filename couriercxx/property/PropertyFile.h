/*
 * PropertyFile.h
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_PROPERTY_PROPERTYFILE_H_
#define COURIERCXX_PROPERTY_PROPERTYFILE_H_

#include <cstdint>
#include <map>
#include <string>

#include "IProperty.h"

/**
 * Property file
 */
class PropertyFile: public IProperty {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string path
	 */
	PropertyFile(std::string path);

	/**
	 * Destructor
	 */
	virtual ~PropertyFile();

	/**
	 * Open config
	 *
	 * \return 0 - if success, -1 if error
	 */
	int open();

	/**
	 * Close config
	 *
	 * \return 0 - if success, -1 if error
	 */
	int close();

	/**
	 * Get uint8_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint8_t* - value
	 */
	uint8_t* getUInt8(std::string paramName);

	/**
	 * Set uint8_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint8_t value - param value
	 */
	void setUInt8(std::string paramName, uint8_t value);

	/**
	 * Get int8_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int8_t* - value
	 */
	int8_t* getInt8(std::string paramName);

	/**
	 * Set int8_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int8_t value - param value
	 */
	void setInt8(std::string paramName, int8_t value);

	/**
	 * Get uint16_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint16_t* - value
	 */
	uint16_t* getUInt16(std::string paramName);

	/**
	 * Set uint16_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint16_t value - param value
	 */
	void setUInt16(std::string paramName, uint16_t value);

	/**
	 * Get int16_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int16_t* - value
	 */
	int16_t* getInt16(std::string paramName);

	/**
	 * Set int16_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int16_t value - param value
	 */
	void setInt16(std::string paramName, int16_t value);

	/**
	 * Get uint32_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint32_t* - value
	 */
	uint32_t* getUInt32(std::string paramName);

	/**
	 * Set uint32_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint32_t value - param value
	 */
	void setUInt32(std::string paramName, uint32_t value);

	/**
	 * Get int32_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int32_t* - value
	 */
	int32_t* getInt32(std::string paramName);

	/**
	 * Set int32_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int32_t value - param value
	 */
	void setInt32(std::string paramName, int32_t value);

	/**
	 * Get uint64_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint64_t* - value
	 */
	uint64_t* getUInt64(std::string paramName);

	/**
	 * Set uint64_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint64_t value - param value
	 */
	void setUInt64(std::string paramName, uint64_t value);

	/**
	 * Get int64_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int64_t* - value
	 */
	int64_t* getInt64(std::string paramName);

	/**
	 * Set int64_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int64_t value - param value
	 */
	void setInt64(std::string paramName, int64_t value);

	/**
	 * Get float param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return float* - value
	 */
	float* getFloat(std::string paramName);

	/**
	 * Set float param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] float value - param value
	 */
	void setFloat(std::string paramName, float value);

	/**
	 * Get double param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return double* - value
	 */
	double* getDouble(std::string paramName);

	/**
	 * Set double param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] double value - param value
	 */
	void setDouble(std::string paramName, double value);

	/**
	 * Get string param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return string* - value
	 */
	std::string* getString(std::string paramName);

	/**
	 * Set string param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] string value - param value
	 */
	void setString(std::string paramName, std::string value);

	/**
	 * Get bool param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return bool* - value
	 */
	bool* getBool(std::string paramName);

	/**
	 * Set bool param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] bool value - param value
	 */
	void setBool(std::string paramName, bool value);

private:
	std::string path;
	std::map<std::string, std::string> properties;

	/**
	 * Save properties
	 *
	 * \return - 0 if success, -1 if error
	 */
	int save();

	/**
	 * Load properties
	 *
	 * \return - 0 if success, -1 if error
	 */
	int load();
};

#endif /* COURIERCXX_PROPERTY_PROPERTYFILE_H_ */
