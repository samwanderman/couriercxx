/*
 * BluetoothPortBase.cpp
 *
 *  Created on: 28.01.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "BluetoothPortBase.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "../../logger/Log.h"

#define MAX_DEVICES	16
#define SEARCH_TIME	8

BluetoothPortBase::BluetoothPortBase() : IConnectorBase() { }

BluetoothPortBase::BluetoothPortBase(std::string addr) : BluetoothPortBase() {
	this->addr = addr;
}

BluetoothPortBase::~BluetoothPortBase() { }

int BluetoothPortBase::open() {
	if (isOpen()) {
		return -1;
	}

	if (addr.length() == 0) {
		devId = hci_get_route(nullptr);
	} else {
		devId = hci_devid(addr.c_str());
	}

	if (devId == -1) {
		return -1;
	}

	fd = hci_open_dev(devId);
	if (fd == -1) {
		return -1;
	}

	return IConnectorBase::open();
}

int BluetoothPortBase::close() {
	if (!isOpen()) {
		return -1;
	}

	::close(fd);
	fd = -1;

	return IConnectorBase::close();
}

std::list<BluetoothDevice*> BluetoothPortBase::search() {
	std::list<BluetoothDevice*> devices;

	int flags = IREQ_CACHE_FLUSH;
	int maxDevices = MAX_DEVICES;

	inquiry_info *foundDevices = new inquiry_info[maxDevices];
	int foundDevicesNumber = hci_inquiry(devId, SEARCH_TIME, maxDevices, nullptr, &foundDevices, flags);

	for (int i = 0; i < foundDevicesNumber; i++) {
		char addr[32];
		memset(addr, 0, 32 * sizeof(char));
		ba2str(&foundDevices[i].bdaddr, addr);
		char name[256];
		memset(name, 0, 256 * sizeof(char));
		if (hci_read_remote_name(fd, &foundDevices[i].bdaddr, sizeof(name), name, 0) == 0) {
			uint32_t type = 0;
			type |= foundDevices[i].dev_class[2];
			type |= foundDevices[i].dev_class[1] << 8;
			type |= foundDevices[i].dev_class[0] << 16;
			devices.push_back(new BluetoothDevice(std::string(addr), std::string(name), type));
		}
	}

	delete[] foundDevices;

	return devices;
}

int BluetoothPortBase::connect(std::string addr, uint8_t svcUUIDInt[16]) {
	Log::debug("BluetoothPortBase.connect()");

	bdaddr_t target;
	str2ba(addr.c_str(), &target);

	// connect to SDP server on remote device
	bdaddr_t addrANY;
	memset(&addrANY, 0, sizeof(addrANY));
	sdp_session_t* session = sdp_connect(&addrANY, &target, SDP_RETRY_IF_BUSY);

	uuid_t svcUUID;

	// specify service UUID
	sdp_uuid128_create(&svcUUID, &svcUUIDInt);

	sdp_list_t* searchList = sdp_list_append(nullptr, &svcUUID);

	// specify that we want list of all attributes
	uint32_t range = 0x0000ffff;
	sdp_list_t* attridList = sdp_list_append(nullptr, &range);

	// get all services than have UUID 0xabcd
	sdp_list_t* responseList = nullptr;
	int status = sdp_service_search_attr_req(session, searchList, SDP_ATTR_REQ_RANGE, attridList, &responseList);
	if (status == -1) {
		sdp_close(session);

		Log::error("sdp_service_search_attr_req() error");

		return -1;
	}
	Log::info("sdp_service_search_attr_req() %i", status);

	sdp_list_t* service = responseList;

	// iterate through services
	while (service != nullptr) {
		// get service record
		sdp_record_t* record = (sdp_record_t*) service->data;
		sdp_list_t* protoList = nullptr;
		Log::debug("Check service");

		// get protos for record
		if (sdp_get_access_protos(record, &protoList) == 0) {
			Log::debug("sdp_get_access_protos() success");
	        sdp_list_t *proto = protoList;

	        // iterate through protos
	        while (proto) {
	            sdp_list_t *pds = (sdp_list_t*) proto->data;
	            Log::debug("Check proto");

	            // iterate through sequences
	            while (pds) {
	            	Log::debug("Check pds");
	                // check the protocol attributes
	                sdp_data_t *d = (sdp_data_t*) pds->data;
	                int protoType = 0;
	                while (d) {
	                	Log::debug("d %i", d->dtd);
	                    switch (d->dtd) {
	                        case SDP_UUID16:
	                        case SDP_UUID32:
	                        case SDP_UUID128:
	                            protoType = sdp_uuid_to_proto(&d->val.uuid);

	                            break;

	                        case SDP_UINT8:
	                            if (protoType == RFCOMM_UUID) {
	                                Log::debug("rfcomm channel: %d\n", d->val.int8);
	                            }

	                            break;
	                    }

	                	d = d->next;
	                }

	            	pds = pds->next;
	            }

	            sdp_list_free((sdp_list_t*) proto->data, 0);

	        	proto = proto->next;
	        }

	        sdp_list_free(protoList, 0);
		}

		Log::debug("found service record 0x%x\n", record->handle);

		sdp_record_free(record);
		service = service->next;
	}

	sdp_close(session);

	return 0;
}
