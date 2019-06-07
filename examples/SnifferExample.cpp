#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "../couriercxx/connector/udp/UDPPortBase.h"
#include "../couriercxx/logger/Log.h"
#include "../couriercxx/net/Net.h"
#include "../couriercxx/net/Protocols.h"
#include "../couriercxx/net/Sniffer.h"

class UDPPortBase;

#define PORT			8880
#define BUFFER_MAX_SIZE	1024

const uint8_t DISCOVERY_REQUEST[]		= { 0x52, 0x45, 0x51, 0x55, 0x45, 0x53, 0x54 };
const uint16_t DISCOVERY_REQUEST_SIZE	= 7;
const uint8_t DISCOVERY_RESPONSE[]		= { 0x52, 0x45, 0x53, 0x50, 0x4f, 0x4e, 0x53, 0x45 };
const uint16_t DISCOVERY_RESPONSE_SIZE	= 8;

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);
	Log::info("Program has started");

	auto func = [](const uint8_t* packet, uint32_t packetSize) {
		ETHPacket ethPacket(packet);
		uint32_t ethPacketSize = 14;

		IPPacket ipPacket(packet + ethPacketSize);
		uint32_t ipHeaderSize = IP_HL(&ipPacket) * 4;

		UDPPacket udpPacket(packet + ethPacketSize + ipHeaderSize);
		uint32_t udpHeaderSize = 8;

		uint32_t dstAddr = ((uint32_t) ipPacket.dstAddr[0] << 24) | ((uint32_t) ipPacket.dstAddr[1] << 16) | ((uint32_t) ipPacket.dstAddr[2] << 8) | ipPacket.dstAddr[3];
		if ((ethPacket.type == 0x0800) && (dstAddr == 0x0affffff) && (ipPacket.protocol == PROTOCOL_UDP) && (udpPacket.dstPort == PORT)) {
			Log::info("---------------");
			Log::log("\r\n");
			for (uint32_t i = 0; i < 14; i++) {
				Log::log("%02x ", packet[i]);

				if (i % 6 == 5) {
					Log::log("\r\n");
				}
			}
			Log::log("\r\n");

			Log::debug("ETHPacket: destinationHostAddress: %u.%u.%u.%u.%u.%u", ethPacket.destinationHostAddress[0], ethPacket.destinationHostAddress[1], ethPacket.destinationHostAddress[2], ethPacket.destinationHostAddress[3], ethPacket.destinationHostAddress[4], ethPacket.destinationHostAddress[5]);
			Log::debug("ETHPacket: sourceHostAddress: %u.%u.%u.%u.%u.%u", ethPacket.sourceHostAddress[0], ethPacket.sourceHostAddress[1], ethPacket.sourceHostAddress[2], ethPacket.sourceHostAddress[3], ethPacket.sourceHostAddress[4], ethPacket.sourceHostAddress[5]);
			Log::debug("ETHPacket: type: %x", ethPacket.type);


			Log::log("\r\n");
			for (uint32_t i = 0; i < ipHeaderSize; i++) {
				Log::log("%02x ", packet[ethPacketSize + i]);

				if (i % 4 == 3) {
					Log::log("\r\n");
				}
			}
			Log::log("\r\n");

			Log::debug("IPPacket: header size: %u", ipHeaderSize);
			Log::debug("IPPacket: version: %x", IP_V(&ipPacket));
			Log::debug("IPPacket: tos: %u", ipPacket.tos);
			Log::debug("IPPacket: payload len: %u", ipPacket.len - ipHeaderSize);
			Log::debug("IPPacket: id: %x", ipPacket.id);
			Log::debug("IPPacket: offset: %u", ipPacket.off);
			Log::debug("IPPacket: ttl: %u", ipPacket.ttl);
			Log::debug("IPPacket: protocol: %u", ipPacket.protocol);
			Log::debug("IPPacket: checksum: %x", ipPacket.checksum);
			Log::debug("IPPacket: srcAddr: %u.%u.%u.%u", ipPacket.srcAddr[0], ipPacket.srcAddr[1], ipPacket.srcAddr[2], ipPacket.srcAddr[3]);
			Log::debug("IPPacket: dstAddr: %u.%u.%u.%u", ipPacket.dstAddr[0], ipPacket.dstAddr[1], ipPacket.dstAddr[2], ipPacket.dstAddr[3]);

			Log::log("\r\n");
			for (uint32_t i = 0; i < udpHeaderSize; i++) {
				Log::log("%02x ", packet[ethPacketSize + ipHeaderSize + i]);

				if (i % 4 == 3) {
					Log::log("\r\n");
				}
			}
			Log::log("\r\n");


			Log::debug("udpPacket src port is %u", udpPacket.srcPort);
			Log::debug("udpPacket dst port is %u", udpPacket.dstPort);
			Log::debug("udpPacket size is %u", udpPacket.len - 8);
			Log::debug("udpPacket checksum is %x", udpPacket.checksum);

			const uint8_t* payload = packet + ethPacketSize + ipHeaderSize + 8;
			for (uint32_t i = 0; i < udpPacket.len - 8; i++) {
				Log::log("%x ", payload[i]);
			}
			Log::log("\r\n");

			if (udpPacket.len - 8 == DISCOVERY_REQUEST_SIZE) {
				bool checked = true;

				for (int i = 0; i < udpPacket.len - 8; i++) {
					if (payload[i] != DISCOVERY_REQUEST[i]) {
						checked = false;

						break;
					}
				}

				if (checked) {
					Log::info("SUCCESS");

					char ip[32];
					memset(ip, 0, 32 * sizeof(char));
					snprintf(ip, 32, "%u.%u.%u.%u", ipPacket.srcAddr[0], ipPacket.srcAddr[1], ipPacket.srcAddr[2], ipPacket.srcAddr[3]);

					Log::info("try to rend response to %s, %u", ip, udpPacket.srcPort);

					UDPPortBase port(ip, udpPacket.srcPort);
					if (port.open() == -1) {
						Log::error("UDPPortBase.open('%s', %u) error", ip, udpPacket.srcPort);
					}

					uint8_t buffer[BUFFER_MAX_SIZE];
					uint32_t bufferSize = 0;
					memset(buffer, 0, BUFFER_MAX_SIZE * sizeof(uint8_t));
					memmove(buffer, DISCOVERY_RESPONSE, DISCOVERY_RESPONSE_SIZE * sizeof(uint8_t));
					bufferSize += DISCOVERY_RESPONSE_SIZE;
					buffer[bufferSize++] = 0x01;
					buffer[bufferSize++] = 0x02;
					buffer[bufferSize++] = 0x03;
					buffer[bufferSize++] = 0x04;

					std::string localIP;
					if (Net::getLocalIPAddr(localIP) != -1) {
						Log::info("local ip is %s", localIP.c_str());
						uint8_t addr[4];

						sscanf(localIP.c_str(), "%u.%u.%u.%u", addr, &addr[1], &addr[2], &addr[3]);
						memmove(&buffer[bufferSize], addr, 4 * sizeof(uint8_t));
						bufferSize += 4;

						if (port.write(buffer, bufferSize) == -1) {
							Log::error("UDPPortBase.write() error");
							perror("");
						} else {
							Log::info("UDPPort.write() success");
						}

						port.close();
					}
				} else {
					Log::error("ERROR");
				}
			}
		}
	};
	Sniffer sniffer("ip", func);

	if (sniffer.enable() == -1) {
		Log::error("Sniffer.enable() error");

		return -1;
	}
	Log::info("Sniffer.enable() success");

	while (true) { }

	if (sniffer.disable() == -1) {
		Log::error("Sniffer.disable() error");

		return -1;
	}
	Log::info("Sniffer.disable() success");

	return 0;
}
