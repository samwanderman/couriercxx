/*
 * BluetoothDevice.cpp
 *
 *  Created on: 28.01.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "BluetoothDevice.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../../logger/Log.h"

BluetoothDevice::BluetoothDevice(std::string addr, std::string name, uint32_t type) : IDevice () {
	this->addr = addr;
	this->name = name;
	this->type = type;
}

BluetoothDevice::~BluetoothDevice() { }

std::string BluetoothDevice::getAddr() {
	return addr;
}

std::string BluetoothDevice::getName() {
	return name;
}

uint32_t BluetoothDevice::getType() {
	return type;
}

int BluetoothDevice::connect() {
	sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	if (sock == -1) {
		return -1;
	}

	struct sockaddr_rc addr = { 0 };
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba(this->addr.c_str(), &addr.rc_bdaddr);

	if (::connect(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
		return -1;
	}

	return 0;
}

int BluetoothDevice::disconnect() {
	close(sock);

	return 0;
}

int BluetoothDevice::read(uint8_t* buffer, uint32_t bufferSize) {
	return ::read(sock, buffer, bufferSize);
}

int BluetoothDevice::write(const uint8_t* buffer, uint32_t bufferSize) {
	return ::write(sock, buffer, bufferSize);
}

void BluetoothDevice::test() {
	bdaddr_t target;
	str2ba(addr.c_str(), &target);

	bdaddr_t source = { 0, 0, 0, 0, 0, 0 };
	sdp_session_t *session = sdp_connect(&source, &target, SDP_RETRY_IF_BUSY);

	uint8_t svcUUIDInt[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xab, 0xcd };
	uuid_t svcUUID;

	sdp_uuid128_create(&svcUUID, &svcUUIDInt);

	sdp_list_t *foundServices = sdp_list_append(nullptr, &svcUUID);

	uint32_t range = 0x0000ffff;
	sdp_list_t *attributes = sdp_list_append(nullptr, &range);

	sdp_list_t *response = nullptr;
	int res = sdp_service_search_attr_req(session, foundServices, SDP_ATTR_REQ_RANGE, attributes, &response);
	if (res == -1) {
		return;
	}

	sdp_list_t *resList = response;
	while (!!(resList = resList->next)) {
        sdp_record_t *rec = (sdp_record_t*) resList->data;
        sdp_list_t *proto_list;

        if (sdp_get_access_protos(rec, &proto_list) == 0) {
        	sdp_list_t *p = proto_list;

        	while (!!(p = p->next)) {
        		sdp_list_t *pds = (sdp_list_t*) p->data;

        		while (!!(pds = pds->next)) {
        			sdp_data_t *d = (sdp_data_t*) pds->data;
        			int proto = 0;
        			while (!!(d = d->next)) {
        				switch (d->dtd) {
                        case SDP_UUID16:
                        case SDP_UUID32:
                        case SDP_UUID128:
                            proto = sdp_uuid_to_proto(&d->val.uuid);

                            break;

                        case SDP_UINT8:
                            if(proto == RFCOMM_UUID) {
                                Log::debug("rfcomm channel: %d\n", d->val.int8);
                            }

                            break;
        				}
        			}
        		}

        		sdp_list_free((sdp_list_t*) p->data, 0);
        	}

        	sdp_list_free(proto_list, 0);
        }

        Log::debug("found service record 0x%x\n", rec->handle);

        sdp_record_free(rec);
	}

	sdp_close(session);
}
