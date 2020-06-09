/*
 * Sniffer.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "../network/Sniffer.h"

#ifndef _WIN32

#include <pcap/bpf.h>
#include <cstdio>
#include <thread>

#include "../logger/Log.h"
#include "../network/Protocols.h"

#define ERROR_BUFFER_SIZE	1024

#undef DEBUG

Sniffer::Sniffer(std::string filter, std::function<void (const uint8_t* packet, uint32_t packetSize)> callback) {
	this->callback = callback;
	this->filter = filter;
}

Sniffer::~Sniffer() { }

int Sniffer::enable() {
	if (handle != nullptr) {
		return -1;
	}

	char errorBuffer[ERROR_BUFFER_SIZE];

	char* dev = pcap_lookupdev(errorBuffer);
	if (dev == nullptr) {
		Log::error("pcap_lookupdev() error:\r\n%s", errorBuffer);

		return -1;
	}

	bpf_u_int32 net;
	bpf_u_int32 mask;

	if (pcap_lookupnet(dev, &net, &mask, errorBuffer) == -1) {
		Log::error("pcap_lookupnet(%s) error:\r\n%s", dev, errorBuffer);
		net = 0;
		mask = 0;
	}

	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errorBuffer);
	if (handle == nullptr) {
		Log::error("pcap_open_live(%s) error", dev);

		return -1;
	}

	struct bpf_program fp;

	if (pcap_compile(handle, &fp, filter.c_str(), 0, net) == -1) {
		Log::error("pcap_compiled(\"%s\") error:\r\n%s", filter.c_str(), pcap_geterr(handle));

		return -1;
	}

	if (pcap_setfilter(handle, &fp) == -1) {
		Log::error("pcap_setfilter() error:\r\n%s", pcap_geterr(handle));

		return -1;
	}

	stopMutex.unlock();
	running = true;

	auto func = [this]() {
		stopMutex.lock();

		while (running) {
			struct pcap_pkthdr header;
			const uint8_t* packet = pcap_next(handle, &header);
			if (packet == nullptr) {
				continue;
			}

#ifdef DEBUG
			Log::debug("total packet len is %d", header.len);

			ETHPacket ethPacket(packet);

			Log::debug("ETHPacket: destinationHostAddress: %u.%u.%u.%u.%u.%u", ethPacket.destinationHostAddress[0], ethPacket.destinationHostAddress[1], ethPacket.destinationHostAddress[2], ethPacket.destinationHostAddress[3], ethPacket.destinationHostAddress[4], ethPacket.destinationHostAddress[5]);
			Log::debug("ETHPacket: sourceHostAddress: %u.%u.%u.%u.%u.%u", ethPacket.sourceHostAddress[0], ethPacket.sourceHostAddress[1], ethPacket.sourceHostAddress[2], ethPacket.sourceHostAddress[3], ethPacket.sourceHostAddress[4], ethPacket.sourceHostAddress[5]);
			Log::debug("ETHPacket: type: %x", ethPacket.type);
#endif
			uint32_t ethPacketSize = 14;

			IPPacket ipPacket(packet + ethPacketSize);
			uint32_t ipPacketSize = IP_HL(&ipPacket) * 4;
			if (ipPacketSize < 20) {
				Log::error("Invalid IP header length: %u bytes", ipPacketSize);

				continue;
			}
#ifdef DEBUG
			Log::debug("IPPacket: header size: %u", IP_HL(&ipPacket) * 4);
			Log::debug("IPPacket: vhl: %x (version %x, ethernet header length %u)", ipPacket.vhl, ipPacket.vhl >> 4, ipPacket.vhl & 0xf);
			Log::debug("IPPacket: tos: %u", ipPacket.tos);
			Log::debug("IPPacket: len: %u", ipPacket.len);
			Log::debug("IPPacket: id: %x", ipPacket.id);
			Log::debug("IPPacket: offset: %u", ipPacket.off);
			Log::debug("IPPacket: ttl: %u", ipPacket.ttl);
			Log::debug("IPPacket: protocol: %u", ipPacket.protocol);
			Log::debug("IPPacket: checksum: %x", ipPacket.checksum);
			Log::debug("IPPacket: srcAddr: %u.%u.%u.%u", ipPacket.srcAddr[0], ipPacket.srcAddr[1], ipPacket.srcAddr[2], ipPacket.srcAddr[3]);
			Log::debug("IPPacket: dstAddr: %u.%u.%u.%u", ipPacket.dstAddr[0], ipPacket.dstAddr[1], ipPacket.dstAddr[2], ipPacket.dstAddr[3]);

			uint32_t otherProtocolsSize = 0;

			switch (ipPacket.protocol) {
			case PROTOCOL_TCP: {
				TCPPacket tcpPacket(packet + ethPacketSize + ipPacketSize);
				uint32_t tcpPacketSize = TCP_OFFSET(&tcpPacket) * 4;
				otherProtocolsSize = tcpPacketSize;
				if (tcpPacketSize < 20) {
					Log::error("Invalid TCP header length: %u bytes", tcpPacketSize);

					continue;
				}

				Log::debug("TCPPacket: source port: %u", tcpPacket.srcPort);
				Log::debug("TCPPacket: destination port: %u", tcpPacket.dstPort);
				Log::debug("TCPPacket: seq num: %u", tcpPacket.seqNum);
				Log::debug("TCPPacket: ack num: %u", tcpPacket.ackNum);
				Log::debug("TCPPacket: offset: %u %u", tcpPacket.offset >> 4, TCP_OFFSET(&tcpPacket) * 4);
				Log::debug("TCPPacket: flags: %x", tcpPacket.flags);
				Log::debug("TCPPacket: window: %u", tcpPacket.window);
				Log::debug("TCPPacket: checksum: %x", tcpPacket.checksum);
				Log::debug("TCPPacket: ptr: %u", tcpPacket.ptr);
			} break;

			case PROTOCOL_UDP: {
				UDPPacket udpPacket(packet + ethPacketSize + ipPacketSize);
				uint16_t udpPacketSize = 8;
				otherProtocolsSize = udpPacketSize;

				Log::debug("UDPPacket: source port: %u", udpPacket.srcPort);
				Log::debug("UDPPacket: destination port: %u", udpPacket.dstPort);
				Log::debug("UDPPacket: total length: %u", udpPacket.len);
				Log::debug("UDPPacket: payload length: %u", udpPacket.len - 8);
				Log::debug("UDPPacket: checksum: %x", udpPacket.checksum);
			} break;
			}

			uint8_t* payload = (uint8_t*) (packet + ethPacketSize + ipPacketSize + otherProtocolsSize);
			uint32_t payloadSize = header.len - (ethPacketSize + ipPacketSize + otherProtocolsSize);
			Log::debug("payloadSize: %u", payloadSize);
			Log::debug("%s", payload);
#endif

			callback(packet, header.len);
		}

		pcap_close(handle);

		stopMutex.unlock();
	};
	std::thread th(func);
	th.detach();

	return 0;
}

int Sniffer::disable() {
	if (handle == nullptr) {
		return -1;
	}

	running = false;

	stopMutex.lock();

	return 0;
}

#endif
