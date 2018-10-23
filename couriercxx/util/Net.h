/*
 * Net.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_UTIL_NET_H_
#define COURIERCXX_UTIL_NET_H_

#include <string>

/**
 * Class for net operations
 */
class Net {
public:
	/**
	 * Get local machine ip address
	 *
	 * \param[out] sting addr - addr
	 *
	 * \return string IP addr
	 */
	static int getLocalIPAddr(std::string& addr);
};

#endif /* COURIERCXX_UTIL_NET_H_ */
