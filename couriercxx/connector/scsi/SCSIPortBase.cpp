/*
 * SCSIPortBase.cpp
 *
 *  Created on: 25.04.2019 г.
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SCSIPortBase.h"

#include <fcntl.h>
#include <scsi/sg.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>

#include "../../logger/Log.h"

#define BUFFER_SIZE			1024
#define ERROR_BUFFER_SIZE	0xff

#define INQ_REPLY_LEN		0xff
#define TIMEOUT				20000
#define WRITE_LEN			0xff

void printHeader(sg_io_hdr_t*);

SCSIPortBase::SCSIPortBase(std::string port) {
	this->port = port;
}

SCSIPortBase::~SCSIPortBase() { }

int SCSIPortBase::open() {
	fd = ::open(this->port.c_str(), O_RDWR);

	if (fd < 0) {
		return -1;
	}

	// Check if device support SCSI and its version
	int version = 0;
	if ((ioctl(fd, SG_GET_VERSION_NUM, &version) < 0) || (version < 30000)) {
		return -1;
	}

	return fd;
}

int SCSIPortBase::close() {
	if (fd != -1) {
		return ::close(fd);
	}

	return -1;
}

int SCSIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	return 0;
}

int SCSIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	Log::log("------->>>\r\n");
	for (uint32_t i = 0; i < bufferSize; i++) {
		Log::log("%02x ", buffer[i]);
	}
	Log::log("\r\n-------<<<\r\n");

	uint8_t senseBuffer[32];
	memset(senseBuffer, 0, sizeof(senseBuffer));

	uint8_t cmd[10];
	cmd[0] = 0x2a;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	cmd[8] = bufferSize;
	cmd[9] = 0;

	sg_io_hdr_t* header = (sg_io_hdr_t*) malloc(sizeof(sg_io_hdr_t));
	if (header == nullptr) {
		return -1;
	}

	memset(header, 0, sizeof(sg_io_hdr_t));
	header->interface_id = 'S';
	header->cmdp = cmd;
	header->cmd_len = sizeof(cmd);
	header->mx_sb_len = sizeof(senseBuffer);
	header->dxfer_direction = SG_DXFER_FROM_DEV;
	header->dxfer_len = bufferSize;
	header->dxferp = (void*) buffer;
	header->sbp = senseBuffer;
	header->timeout = TIMEOUT;

	int res = ioctl(fd, SG_IO, header);
	if (res < 0) {
		return -1;
	}

	printHeader(header);

    free(header);

    return 0;
}

int SCSIPortBase::getDeviceInfo(bool extended, uint8_t pageCode) {
	uint8_t senseBuffer[32];
	memset(senseBuffer, 0, sizeof(senseBuffer));

	uint8_t buffer[256];
	memset(buffer, 0, sizeof(buffer));

	uint8_t cmd[6];
	cmd[0] = 0x12;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = INQ_REPLY_LEN;
	cmd[5] = 0;

	sg_io_hdr_t* header = (sg_io_hdr_t*) malloc(sizeof(sg_io_hdr_t));
	if (header == nullptr) {
		return -1;
	}

	memset(header, 0, sizeof(sg_io_hdr_t));
	header->interface_id = 'S';
	header->cmd_len = sizeof(cmd);
	header->mx_sb_len = sizeof(senseBuffer);
	header->dxfer_direction = SG_DXFER_FROM_DEV;
	header->dxfer_len = INQ_REPLY_LEN;
	header->dxferp = buffer;
	header->cmdp = cmd;
	header->sbp = senseBuffer;
	header->timeout = TIMEOUT;

	int res = ioctl(fd, SG_IO, header);
	if (res < 0) {
		return -1;
	}

    if ((header->info & SG_INFO_OK_MASK) != SG_INFO_OK) {
        if (header->sb_len_wr > 0) {
            Log::debug("INQUIRY sense data: ");
            for (int k = 0; k < header->sb_len_wr; k++) {
                if ((k > 0) && (0 == (k % 10))) {
                    Log::log("\n");
                }

                Log::log("0x%02x ", senseBuffer[k]);
            }
            Log::log("\n");
        }

        Log::debug("INQUIRY SCSI status=0x%x\n", header->status);

        if (header->masked_status) {
            Log::debug("INQUIRY SCSI status=0x%x\n", header->status);
        }

        if (header->host_status) {
        	Log::debug("INQUIRY host_status=0x%x\n", header->host_status);
        }

        if (header->driver_status) {
        	Log::debug("INQUIRY driver_status=0x%x\n", header->driver_status);
        }

        printHeader(header);

		free(header);

		return -1;
	} else {
		char* p = (char*) buffer;
		Log::debug("Some of the INQUIRY command's response:\n");
		Log::debug("    %.8s  %.16s  %.4s\n", p + 8, p + 16, p + 32);
		Log::debug("INQUIRY duration=%u millisecs, resid=%d\n", header->duration, header->resid);

		printHeader(header);

    }

    free(header);

    return 0;
}

void printHeader(sg_io_hdr_t* header) {
	Log::debug("-------------------------");
	Log::debug("OK");
	Log::debug("InterfaceId: %c", header->interface_id);
	Log::debug("durtion: %u", header->duration);
	Log::debug("info: %x", header->info);
	Log::debug("dxfer_direction: %i", header->dxfer_direction);
	Log::debug("cmd_len: %u", header->cmd_len);
	Log::debug("cmd: ");
	for (int i = 0; i < header->cmd_len; i++) {
		Log::log("%02x ", (uint8_t) header->cmdp[i]);
	}
	Log::log("\r\n");
	Log::debug("mx_sb_len: %u", header->mx_sb_len);
	Log::debug("iovec_count: %u", header->iovec_count);
	Log::debug("dxfer_len: %u", header->dxfer_len);
	Log::debug("resid: %i", header->resid);
	Log::debug("dxferp: ");
	for (uint32_t i = 0; i < header->dxfer_len; i++) {
		Log::log("%02x ", ((uint8_t*) header->dxferp)[i]);
	}
	Log::log("\r\n");
	Log::debug("status: %u", header->status);
	Log::debug("masked_status: %u", header->masked_status);
	Log::debug("msg_status: %u", header->msg_status);
	Log::debug("driver_status %u", header->driver_status);
	Log::debug("host_status: %u", header->host_status);
	Log::debug("sb_len_wr: %u", header->sb_len_wr);
	Log::debug("sbp: ");
	for (int i = 0; i < header->sb_len_wr; i++) {
		Log::log("%02x ", (uint8_t) header->sbp[i]);
	}
	Log::log("\r\n");
	Log::debug("flags: %x", header->flags);
	Log::debug("timeout: %i", header->timeout);
	Log::debug("-------------------------");
}

