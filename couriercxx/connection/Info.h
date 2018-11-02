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
 * Class for connection info data
 */
class Info {
public:
	/**
	 * Constructor
	 *
	 * \param[in] int32_t id - connection id
	 * \param[in] string name - conenction name
	 */
	Info(int32_t id, std::string name);

	/**
	 * Constructor
	 *
	 * \param[in] int32_t id - connection id
	 */
	Info(int32_t id);

	/**
	 * Destructor
	 */
	virtual ~Info();

	/**
	 * Get connection id
	 *
	 * \return connection id
	 */
	int32_t getId();

	/**
	 * Get connection name
	 *
	 * \return connection name
	 */
	std::string getName();

private:
	int32_t id = -1;
	std::string name = "";
};

}

#endif /* COURIERCXX_CONNECTION_INFO_H_ */
