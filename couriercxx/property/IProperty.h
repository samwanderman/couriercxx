/*
 * IProperty.h
 *
 *  Created on: 14.10.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_PROPERTY_IPROPERTY_H_
#define COURIERCXX_PROPERTY_IPROPERTY_H_

#include <cstdint>
#include <string>

/**
 * Config interface
 */
class IProperty {
public:
	/**
	 * Constructor
	 */
	IProperty();

	/**
	 * Destructor
	 */
	virtual ~IProperty();

	/**
	 * Open config
	 *
	 * \return 0 - if success, -1 if error
	 */
	virtual int open();

	/**
	 * Close config
	 *
	 * \return 0 - if success, -1 if error
	 */
	virtual int close();

	/**
	 * Get uint8_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint8_t* - value
	 */
	virtual uint8_t* getUInt8(std::string paramName);

	/**
	 * Get uint8_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint8_t defaultValue - default value
	 *
	 * \return uint8_t* - value
	 */
	virtual uint8_t* getUInt8(std::string paramName, uint8_t defaultValue);

	/**
	 * Set uint8_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint8_t value - param value
	 */
	virtual void setUInt8(std::string paramName, uint8_t value);

	/**
	 * Get int8_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int8_t* - value
	 */
	virtual int8_t* getInt8(std::string paramName);

	/**
	 * Get int8_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int8_t defaultValue - default value
	 *
	 * \return int8_t* - value
	 */
	virtual int8_t* getInt8(std::string paramName, int8_t defaultValue);

	/**
	 * Set int8_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int8_t value - param value
	 */
	virtual void setInt8(std::string paramName, int8_t value);

	/**
	 * Get uint16_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint16_t* - value
	 */
	virtual uint16_t* getUInt16(std::string paramName);

	/**
	 * Get uint16_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint16_t defaultValue - default value
	 *
	 * \return uint16_t* - value
	 */
	virtual uint16_t* getUInt16(std::string paramName, uint16_t defaultValue);

	/**
	 * Set uint16_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint16_t value - param value
	 */
	virtual void setUInt16(std::string paramName, uint16_t value);

	/**
	 * Get int16_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int16_t* - value
	 */
	virtual int16_t* getInt16(std::string paramName);

	/**
	 * Get int16_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int16_t defaultValue - default value
	 *
	 * \return int16_t* - value
	 */
	virtual int16_t* getInt16(std::string paramName, int16_t defaultValue);

	/**
	 * Set int16_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int16_t value - param value
	 */
	virtual void setInt16(std::string paramName, int16_t value);

	/**
	 * Get uint32_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint32_t* - value
	 */
	virtual uint32_t* getUInt32(std::string paramName);

	/**
	 * Get uint32_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint32_t defaultValue - default value
	 *
	 * \return uint32_t* - value
	 */
	virtual uint32_t* getUInt32(std::string paramName, uint32_t defaultValue);

	/**
	 * Set uint32_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint32_t value - param value
	 */
	virtual void setUInt32(std::string paramName, uint32_t value);

	/**
	 * Get int32_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int32_t* - value
	 */
	virtual int32_t* getInt32(std::string paramName);

	/**
	 * Get int32_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int32_t defaultValue - default value
	 *
	 * \return int32_t* - value
	 */
	virtual int32_t* getInt32(std::string paramName, int32_t defaultValue);

	/**
	 * Set int32_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int32_t value - param value
	 */
	virtual void setInt32(std::string paramName, int32_t value);

	/**
	 * Get uint64_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return uint64_t* - value
	 */
	virtual uint64_t* getUInt64(std::string paramName);

	/**
	 * Get uint64_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint64_t defaultValue - default value
	 *
	 * \return uint64_t* - value
	 */
	virtual uint64_t* getUInt64(std::string paramName, uint64_t defaultValue);

	/**
	 * Set uint64_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] uint64_t value - param value
	 */
	virtual void setUInt64(std::string paramName, uint64_t value);

	/**
	 * Get int64_t param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return int64_t* - value
	 */
	virtual int64_t* getInt64(std::string paramName);

	/**
	 * Get int64_t param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int64_t defaultValue - default value
	 *
	 * \return int64_t* - value
	 */
	virtual int64_t* getInt64(std::string paramName, int64_t defaultValue);

	/**
	 * Set int64_t param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] int64_t value - param value
	 */
	virtual void setInt64(std::string paramName, int64_t value);

	/**
	 * Get float param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return float* - value
	 */
	virtual float* getFloat(std::string paramName);

	/**
	 * Get float param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] float defaultValue - default value
	 *
	 * \return float* - value
	 */
	virtual float* getFloat(std::string paramName, float defaultValue);

	/**
	 * Set float param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] float value - param value
	 */
	virtual void setFloat(std::string paramName, float value);

	/**
	 * Get double param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return double* - value
	 */
	virtual double* getDouble(std::string paramName);

	/**
	 * Get double param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] double defaultValue - default value
	 *
	 * \return double* - value
	 */
	virtual double* getDouble(std::string paramName, double defaultValue);

	/**
	 * Set double param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] double value - param value
	 */
	virtual void setDouble(std::string paramName, double value);

	/**
	 * Get string param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return string* - value
	 */
	virtual std::string* getString(std::string paramName);

	/**
	 * Get string param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] string defaultValue - default value
	 *
	 * \return string* - value
	 */
	virtual std::string* getString(std::string paramName, std::string defaultValue);

	/**
	 * Set string param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] string value - param value
	 */
	virtual void setString(std::string paramName, std::string value);

	/**
	 * Get bool param
	 *
	 * \param[in] string paramName - param name
	 *
	 * \return bool* - value
	 */
	virtual bool* getBool(std::string paramName);

	/**
	 * Get bool param and return default value if not found
	 *
	 * \param[in] string paramName - param name
	 * \param[in] bool defaultValue - default value
	 *
	 * \return bool* - value
	 */
	virtual bool* getBool(std::string paramName, bool defaultValue);

	/**
	 * Set bool param
	 *
	 * \param[in] string paramName - param name
	 * \param[in] bool value - param value
	 */
	virtual void setBool(std::string paramName, bool value);
};

#endif /* COURIERCXX_PROPERTY_IPROPERTY_H_ */
