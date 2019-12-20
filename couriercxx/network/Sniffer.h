/*
 * Sniffer.h
 *
 *  Created on: Oct 29, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NETWORK_SNIFFER_H_
#define COURIERCXX_NETWORK_SNIFFER_H_

#ifdef _WIN32
#else
#include <pcap/pcap.h>
#endif
#include <cstdint>
#include <functional>
#include <string>
#include <mutex>

/**
 * Sniffer class
 */
class Sniffer {
public:
	/**
	 * Constructor
	 *
	 * \param[in] string filter - string with filter
	 * \param[in] callback - callback on filter match
	 */
	Sniffer(std::string filter, std::function<void (const uint8_t* packet, uint32_t packetSize)> callback);

	/**
	 * Destructor
	 */
	virtual ~Sniffer();

	/**
	 * Enable capturing
	 */
	int enable();

	/**
	 * Disable capturing
	 */
	int disable();

private:
	bool running = false;
	std::mutex stopMutex;
#ifdef _WIN32
#else
	pcap_t* handle = nullptr;
#endif
	std::string filter = "";
	std::function<void (const uint8_t* packet, uint32_t packetSize)> callback = nullptr;
};

#endif /* COURIERCXX_NETWORK_SNIFFER_H_ */
