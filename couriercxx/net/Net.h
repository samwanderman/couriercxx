/*
 * Net.h
 *
 *  Created on: Oct 16, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NET_NET_H_
#define COURIERCXX_NET_NET_H_

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
	 * \param[out] sting addr - addr
	 *
	 * \return string IP addr
	 */
	static int getLocalIPAddr(std::string& addr);

	/**
	 * Get local machine net params
	 *
	 * \param[out] Addr addr - addr
	 *
	 * \return 0 if succes, -1 if error
	 */
	static int get(Addr &addr);
};

#endif /* COURIERCXX_NET_NET_H_ */
