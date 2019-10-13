/*
 * Value.h
 *
 *  Created on: 15.02.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_DB_VALUE_H_
#define COURIERCXX_DB_VALUE_H_

#include <pqxx/binarystring.hxx>
#include <cstdint>
#include <typeindex>

namespace DB {

/**
 * Base value
 */
template<typename T>
struct Value {
	/**
	 * Constructor
	 */
	Value() { }

	/**
	 * Constructor
	 *
	 * \param[in] <T> value - value
	 */
	Value(T* value) {
		this->value = value;
	}

	T* value = nullptr;
	std::type_index type = typeid(T);
};

typedef Value<const char*> StringValue;
typedef Value<pqxx::binarystring> ArrayValue;
typedef Value<uint8_t> UInt8Value;
typedef Value<int8_t> Int8Value;
typedef Value<uint16_t> UInt16Value;
typedef Value<int16_t> Int16Value;
typedef Value<uint32_t> UInt32Value;
typedef Value<int32_t> Int32Value;
typedef Value<uint64_t> UInt64Value;
typedef Value<int64_t> Int64Value;
typedef Value<bool> BoolValue;

const std::type_index typeBool(typeid(BoolValue));
const std::type_index typeUINT8T(typeid(UInt8Value));
const std::type_index typeINT8T(typeid(Int8Value));
const std::type_index typeUINT16T(typeid(UInt16Value));
const std::type_index typeINT16T(typeid(Int16Value));
const std::type_index typeUINT32T(typeid(UInt32Value));
const std::type_index typeINT32T(typeid(Int32Value));
const std::type_index typeUINT64T(typeid(UInt64Value));
const std::type_index typeINT64T(typeid(Int64Value));
const std::type_index typeArray(typeid(ArrayValue));
const std::type_index typeString(typeid(StringValue));

};

#endif /* COURIERCXX_DB_VALUE_H_ */
