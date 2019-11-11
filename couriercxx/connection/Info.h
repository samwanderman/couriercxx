/*
 * Info.h
 *
 *  Created on: Oct 19, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_CONNECTION_INFO_H_
#define COURIERCXX_CONNECTION_INFO_H_

#include <cstdint>
#include <string>

namespace Connection {

/**
 * Connection info struct
 */
struct Info {
	/**
	 * Constructor
	 *
	 * \param[in] int32_t id - connection id
	 * \param[in] string name - connection name
	 * \param[in] uint64_t commandTimeout - command timeout
	 */
	Info(int32_t id, std::string name, uint64_t commandTimeout);

	/**
	 * Constructor
	 *
	 * \param[in] int32_t id - connection id
	 */
	Info(int32_t id);

	/**
	 * Constructor
	 */
	Info();

	int32_t id = -1;
	std::string name = "";
	uint64_t commandTimeout = 0;
};
typedef struct Info Info;

}

#endif /* COURIERCXX_CONNECTION_INFO_H_ */
