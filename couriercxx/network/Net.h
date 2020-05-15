/*
 * Net.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_NET_H_
#define COURIERCXX_NETWORK_NET_H_

#include <cstdint>
#include <string>

/**
 * Class for net operations
 */
class Net {
public:
	struct Addr {
		uint8_t ip[4];
		uint8_t mask[4];
		uint8_t gateway[4];
		uint8_t dnsNameserver1[4];
		uint8_t dnsNameserver2[4];
	};
	typedef struct Addr Addr;

	/**
	 * Get local machine ip address
	 *
	 * \param[out] addr - addr
	 *
	 * \return
	 *			- 0 if success
	 *			- -1 if error
	 */
	static int getLocalIPAddr(std::string& addr);

	/**
	 * Get local machine net params
	 *
	 * \param[out] addr - addr
	 *
	 * \return
	 * 			- 0 if success
	 * 			- -1 if error
	 */
	static int get(Addr &addr);

	/**
	 * Convert ip to string
	 *
	 * \param[in] ip - ip
	 *
	 * \return string representation of ip
	 */
	static std::string ipToStr(uint8_t ip[4]);
};

#endif /* COURIERCXX_NETWORK_NET_H_ */
