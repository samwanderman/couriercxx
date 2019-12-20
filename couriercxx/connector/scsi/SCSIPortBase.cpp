/*
 * SCSIPortBase.cpp
 *
 *  Created on: 25.04.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "SCSIPortBase.h"

#include <fcntl.h>
#ifdef _WIN32
#else
#include <scsi/sg.h>
#include <sys/ioctl.h>
#endif

#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include "../../logger/Log.h"

#define BUFFER_SIZE			1024
#define ERROR_BUFFER_SIZE	0xff

#define INQ_REPLY_LEN		0xff
#define TIMEOUT				20000
#define WRITE_LEN			0xff

#ifdef _WIN32
#else
void printHeader(sg_io_hdr_t& hdr);
#endif

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
//	int version = 0;
//	if ((ioctl(fd, SG_GET_VERSION_NUM, &version) < 0) || (version < 30000)) {
//		return -1;
//	}

	return fd;
}

int SCSIPortBase::close() {
	if (fd != -1) {
		return ::close(fd);
	}

	return -1;
}

int SCSIPortBase::read(uint8_t* buffer, uint32_t bufferSize) {
	uint8_t senseBuffer[32];
	memset(senseBuffer, 0, sizeof(senseBuffer));

#ifdef _WIN32
#else
	uint8_t cmd[10];
	cmd[0] = 0x2a;//28
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	cmd[8] = bufferSize;
	cmd[9] = 0;

	sg_io_hdr_t header;

	memset(&header, 0, sizeof(sg_io_hdr_t));
	header.interface_id = 'S';
	header.cmd_len = sizeof(cmd);
	header.mx_sb_len = sizeof(senseBuffer);
	header.dxfer_direction = SG_DXFER_TO_DEV;
	header.dxfer_len = bufferSize;
	header.dxferp = buffer;
	header.cmdp = cmd;
	header.sbp = senseBuffer;
	header.timeout = TIMEOUT;

	int res = ioctl(fd, SG_IO, &header);
	if (res < 0) {
		return -1;
	}

	printHeader(header);
#endif

    return 0;
}

int SCSIPortBase::write(const uint8_t* buffer, uint32_t bufferSize) {
	uint8_t senseBuffer[32];
	memset(senseBuffer, 0, sizeof(senseBuffer));

	uint8_t buffer2[bufferSize];
	memset(buffer2, 0, sizeof(buffer2));
	memmove(buffer2, buffer, bufferSize * sizeof(uint8_t));

#ifdef _WIN32
#else
	uint8_t cmd[10];
	cmd[0] = 0x2a;//28
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	cmd[8] = bufferSize;
	cmd[9] = 0;

	sg_io_hdr_t header;
	memset(&header, 0, sizeof(sg_io_hdr_t));
	header.interface_id = 'S';
	header.cmd_len = sizeof(cmd);
	header.mx_sb_len = sizeof(senseBuffer);
	header.dxfer_direction = SG_DXFER_TO_FROM_DEV;
	header.dxfer_len = bufferSize;
	header.dxferp = buffer2;
	header.cmdp = cmd;
	header.sbp = senseBuffer;
	header.timeout = TIMEOUT;

	printHeader(header);

	int res = ioctl(fd, SG_IO, &header);
	if (res < 0) {
		return -1;
	}

	printHeader(header);
#endif
    return 0;
}

int SCSIPortBase::getDeviceInfo(bool extended, uint8_t pageCode) {
	uint8_t senseBuffer[32];
	memset(senseBuffer, 0, sizeof(senseBuffer));

	uint8_t buffer[256];
	memset(buffer, 0, sizeof(buffer));

#ifdef _WIN32
#else
	uint8_t cmd[6];
	cmd[0] = 0x12;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = INQ_REPLY_LEN;
	cmd[5] = 0;

	sg_io_hdr_t header;
	memset(&header, 0, sizeof(sg_io_hdr_t));
	header.interface_id = 'S';
	header.cmd_len = sizeof(cmd);
	header.mx_sb_len = sizeof(senseBuffer);
	header.dxfer_direction = SG_DXFER_FROM_DEV;
	header.dxfer_len = INQ_REPLY_LEN;
	header.dxferp = buffer;
	header.cmdp = cmd;
	header.sbp = senseBuffer;
	header.timeout = TIMEOUT;

	int res = ioctl(fd, SG_IO, &header);
	if (res < 0) {
		return -1;
	}

    if ((header.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
        printHeader(header);

		return -1;
	} else {
		char* p = (char*) buffer;
		Log::log("Inquiry:\r\n%.8s  %.16s  %.4s\r\nduration = %u millisecs, resid = %d\r\n", p + 8, p + 16, p + 32, header.duration, header.resid);
		printHeader(header);

    }
#endif
    return 0;
}

#ifdef _WIN32
#else
void printHeader(sg_io_hdr_t& header) {
	Log::debug("-------------------------");
	Log::debug("OK");
	Log::debug("interface_id: %c", header.interface_id);
	Log::debug("duration: %u", header.duration);
	Log::debug("info: %x", header.info);
	Log::debug("dxfer_direction: %i", header.dxfer_direction);
	Log::debug("cmd_len: %u", header.cmd_len);
	Log::debug("cmd: ");
	if (header.cmd_len > 0) {
		for (int i = 0; i < header.cmd_len; i++) {
			Log::log("%02x ", (uint8_t) header.cmdp[i]);
		}
		Log::log("\r\n");
	}
	Log::debug("mx_sb_len: %u", header.mx_sb_len);
	Log::debug("iovec_count: %u", header.iovec_count);
	Log::debug("dxfer_len: %u", header.dxfer_len);
	Log::debug("resid: %i", header.resid);
	Log::debug("dxferp: ");
	if (header.dxfer_len > 0) {
		for (uint32_t i = 0; i < header.dxfer_len; i++) {
			Log::log("%02x ", ((uint8_t*) header.dxferp)[i]);
		}
		Log::log("\r\n");
	}
	Log::debug("status: %u", header.status);
	Log::debug("masked_status: %u", header.masked_status);
	Log::debug("msg_status: %u", header.msg_status);
	Log::debug("driver_status %u", header.driver_status);
	Log::debug("host_status: %u", header.host_status);
	if (header.host_status) {
		perror("");
	}
	Log::debug("sb_len_wr: %u", header.sb_len_wr);
	Log::debug("sbp: ");
	if (header.sb_len_wr > 0) {
		for (int i = 0; i < header.sb_len_wr; i++) {
			Log::log("%02x ", (uint8_t) header.sbp[i]);
		}
		Log::log("\r\n");
	}
	Log::debug("flags: %x", header.flags);
	Log::debug("timeout: %i", header.timeout);
	Log::debug("-------------------------");
}
#endif
