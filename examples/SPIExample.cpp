#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>

#include "../couriercxx/logger/Log.h"

#define PATH	"/dev/spidev0.0"

class SPI {
public:
	SPI() {	}

	virtual ~SPI() { }

	int open() {
		fd = ::open(PATH, O_RDWR);
		if (fd == -1) {
			return -1;
		}

		if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
			Log::error("ioctl(SPI_IOC_WR_MODE) error");

			close();

			return -1;
		}

		if (ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1) {
			Log::error("ioctl(SPI_IOC_RD_MODE) error");

			close();

			return -1;
		}

		if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) {
			Log::error("ioctl(SPI_IOC_WR_BITS_PER_WORD) error");

			close();

			return -1;
		}

		if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) == -1) {
			Log::error("ioctl(SPI_IOC_RD_BITS_PER_WORD) error");

			close();

			return -1;
		}

		if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
			Log::error("ioctl(SPI_IOC_WR_MAX_SPEED_HZ) error");

			close();

			return -1;
		}

		if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1) {
			Log::error("ioctl(SPI_IOC_RD_MAX_SPEED_HZ) error");

			close();

			return -1;
		}

		Log::debug("spi mode:  %d", mode);
		Log::debug("bits per word: %d", bits);
		Log::debug("max speed %d Hz (%d kHz)", speed, speed / 1000);

		return 0;
	}

	int close() {
		if (fd != -1) {
			::close(fd);

			fd = -1;
		}

		return 0;
	}

	int write(const uint8_t* buffer, uint32_t bufferSize) {
		uint8_t outBuffer[bufferSize];
		memset(outBuffer, 0, bufferSize * sizeof(uint8_t));
		struct spi_ioc_transfer tr;
		memset(&tr, 0, sizeof(tr));
		tr.tx_buf = (unsigned long) buffer;
		tr.rx_buf = (unsigned long)outBuffer;
		tr.len = bufferSize;
		tr.bits_per_word = bits;

		int res = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
		if (res == -1) {
			return -1;
		}

		for (int i = 0; i < bufferSize; i++) {
			printf("%x ", outBuffer[i]);
		}
		printf("\r\n");

		return 0;
	}

private:
	int fd = -1;
	uint8_t mode = SPI_MODE_0;
	uint8_t bits = 0;
	uint32_t speed = 500000;
};

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);
	Log::info("Program has started");

	SPI* spi = new SPI();
	if (spi->open() == -1) {
		Log::error("SPI.open() error");

		return -1;
	}
	Log::info("SPI.open() success");

	// HX8357С
	uint8_t CMD_ENABLE_EXTENSION[4] = { 0xb9, 0xff, 0x83, 0x57 };
	spi->write(CMD_ENABLE_EXTENSION, 4);
	usleep(50 * 1000);

	uint8_t CMD_SET_VCOM_VOLTAGE[2] = { 0xb6, 0x2c };
	spi->write(CMD_SET_VCOM_VOLTAGE, 2);

	uint8_t CMD_SLEEP_OFF[1] = { 0x11 };
	spi->write(CMD_SLEEP_OFF, 1);
	usleep(200 * 1000);

	uint8_t CMD_TEARING[2] = { 0x35, 0x00 };
	spi->write(CMD_TEARING, 2);

	uint8_t CMD_PIXEL_FORMAT[2] = { 0x3a, 0x55 };
	spi->write(CMD_PIXEL_FORMAT, 2);

	uint8_t CMD_POWER_CONTROL[7] = { 0xb1, 0x00, 0x15, 0x0d, 0x0d, 0x83, 0x48 };
	spi->write(CMD_POWER_CONTROL, 7);

	uint8_t CMD_HZ[7] = { 0xc0, 0x24, 0x24, 0x01, 0x3c, 0xc8, 0x08 };
	spi->write(CMD_HZ, 7);

	uint8_t CMD_DISPLAY_CYCLE[8] = { 0xb4, 0x02, 0x40, 0x00, 0x2a, 0x2a, 0x0d, 0x4f };
	spi->write(CMD_DISPLAY_CYCLE, 8);

	uint8_t CMD_GAMMA_CURVE1[15] = { 0xe0, 0x00, 0x15, 0x1d, 0x2a, 0x31, 0x42, 0x4c, 0x53, 0x45, 0x40, 0x3b, 0x32, 0x2e, 0x28 };
	spi->write(CMD_GAMMA_CURVE1, 15);

	uint8_t CMD_GAMMA_CURVE2[14] = { 0x24, 0x03, 0x00, 0x15, 0x1d, 0x2a, 0x31, 0x42, 0x4c, 0x53, 0x45, 0x40, 0x3b, 0x32 };
	spi->write(CMD_GAMMA_CURVE2, 14);

	uint8_t CMD_GAMMA_CURVE3[6] = { 0x2e, 0x28, 0x24, 0x03, 0x00, 0x01 };
	spi->write(CMD_GAMMA_CURVE3, 6);

	uint8_t CMD_MEMORY_ACCESS_CONTROL[2] = { 0x36, 0x48 };
	spi->write(CMD_MEMORY_ACCESS_CONTROL, 2);
	usleep(20 * 1000);

	uint8_t CMD_DISPLAY_INVERSION_ON[1] = { 0x21 };
	spi->write(CMD_DISPLAY_INVERSION_ON, 1);
	usleep(20 * 1000);

	uint8_t CMD_DISPLAY_ON[1] = { 0x29 };
	spi->write(CMD_DISPLAY_ON, 1);
	usleep(120 * 1000);

	uint8_t CMD_RED[13] = { 0x2a, 0x00, 0x10, 0x00, 0x10, 0x2b, 0x00, 0x10, 0x00, 0x10, 0x2c, 0xf8, 0x00 };
	spi->write(CMD_RED, 13);

	if (spi->close() == -1) {
		Log::error("SPI.close() error");

		return -1;
	}
	Log::info("SPI.close() success");

	return 0;
}
