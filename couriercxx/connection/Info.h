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

#include "../Types.h"

namespace Connection {

/**
 * Connection info struct
 */
struct Info {
	/**
	 * Constructor
	 *
	 * \param[in] id				- connection id
	 * \param[in] name				- connection name
	 * \param[in] commandTimeout	- command timeout
	 */
	Info(int32_t id, std::string name, Timeout commandTimeout);

	/**
	 * Constructor
	 *
	 * \param[in] id				- connection id
	 * \param[in] name				- connection name
	 * \param[in] commandTimeout	- command timeout
	 * \param[in] reconnectOnErrors	- reconnect on errors
	 * \param[in] reconnectTimeout	- timeout between reconnection attempts
	 */
	Info(int32_t id, std::string name, Timeout commandTimeout, bool reconnectOnErrors, Timeout reconnectTimeout);

	/**
	 * Constructor
	 *
	 * \param[in] id - connection id
	 */
	Info(int32_t id);

	/**
	 * Constructor
	 */
	Info();

	int32_t		id					= -1;
	std::string	name;
	Timeout		commandTimeout		= -1;

	bool		reconnectOnErrors	= false;
	Timeout		reconnectTimeout	= -1;
};
typedef struct Info Info;

}

#endif /* COURIERCXX_CONNECTION_INFO_H_ */
