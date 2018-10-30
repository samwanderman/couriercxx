/*
 * Protocols.h
 *
 *  Created on: Oct 29, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_NET_PROTOCOLS_H_
#define COURIERCXX_NET_PROTOCOLS_H_

#include <cstdint>
#include <cstring>

/**
 * Protocol ID
 */
#define PROTOCOL_TCP	6
#define PROTOCOL_UDP	17

#define ETHERNET_ADDRESS_LEN	6

/**
 * Ethernet packet
 */
struct ETHPacket {
	uint8_t destinationHostAddress[ETHERNET_ADDRESS_LEN];
	uint8_t sourceHostAddress[ETHERNET_ADDRESS_LEN];
	uint16_t type;

	ETHPacket(const uint8_t* buffer) {
		memmove(destinationHostAddress, buffer, ETHERNET_ADDRESS_LEN * sizeof(uint8_t));
		memmove(sourceHostAddress, &buffer[ETHERNET_ADDRESS_LEN], ETHERNET_ADDRESS_LEN * sizeof(uint8_t));
		type = ((uint16_t) buffer[ETHERNET_ADDRESS_LEN * 2] << 8) | buffer[ETHERNET_ADDRESS_LEN * 2 + 1];
	}
};
typedef struct ETHPacket ETHPacket;

/**
 * IP packet
 */
struct IPPacket {
	uint8_t vhl;
	uint8_t tos;
	uint16_t len;
	uint16_t id;
	uint16_t off;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint8_t srcAddr[4];
	uint8_t dstAddr[4];

	IPPacket(const uint8_t* buffer) {
		vhl = buffer[0];
		tos = buffer[1];
		len = ((uint16_t) buffer[2] << 8) | buffer[3];
		id = ((uint16_t) buffer[4] << 8) | buffer[5];
		off = ((uint16_t) buffer[6] << 8) | buffer[7];
		ttl = buffer[8];
		protocol = buffer[9];
		checksum = ((uint16_t) buffer[10] << 8) | buffer[11];
		memmove(srcAddr, &buffer[12], 4 * sizeof(uint8_t));
		memmove(dstAddr, &buffer[16], 4 * sizeof(uint8_t));
	}
};
typedef struct IPPacket IPPacket;

#define IP_HL(ip)		(((ip)->vhl) & 0x0f)
#define IP_V(ip)		(((ip)->vhl) >> 4)

/**
 * TCP packet
 */
struct TCPPacket {
	uint16_t srcPort;
	uint16_t dstPort;
	uint32_t seqNum;
	uint32_t ackNum;
	uint8_t offset;
	uint8_t flags;
	uint16_t window;
	uint16_t checksum;
	uint16_t ptr;

	TCPPacket(const uint8_t* buffer) {
		srcPort = ((uint16_t) buffer[0] << 8) | buffer[1];
		dstPort = ((uint16_t) buffer[2] << 8) | buffer[3];
		seqNum = ((uint32_t) buffer[4] << 24) | ((uint32_t) buffer[5] << 16) | ((uint32_t) buffer[6] << 8) | buffer[7];
		ackNum = ((uint32_t) buffer[8] << 24) | ((uint32_t) buffer[9] << 16) | ((uint32_t) buffer[10] << 8) | buffer[11];
		offset = buffer[12];
		flags = buffer[13];
		window = ((uint16_t) buffer[14] << 8) | buffer[15];
		checksum = ((uint16_t) buffer[16] << 8) | buffer[17];
		ptr = ((uint16_t) buffer[18] << 8) | buffer[19];
	}
};
typedef struct TCPPacket TCPPacket;

#define TCP_OFFSET(tcp) (((tcp)->offset >> 4) & 0xf)

struct UDPPacket {
	uint16_t srcPort;
	uint16_t dstPort;
	uint16_t len;
	uint16_t checksum;

	UDPPacket(const uint8_t* buffer) {
		srcPort = ((uint16_t) buffer[0] << 8) | buffer[1];
		dstPort = ((uint16_t) buffer[2] << 8) | buffer[3];
		len = ((uint16_t) buffer[4] << 8) | buffer[5];
		checksum = ((uint16_t) buffer[6] << 8) | buffer[7];
	}
};

#endif /* COURIERCXX_NET_PROTOCOLS_H_ */
