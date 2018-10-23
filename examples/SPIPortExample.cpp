#include <unistd.h>

#include "../couriercxx/connector/spi/SPIPortBase.h"
#include "../couriercxx/logger/Log.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	SPIPortBase port(64, 65, 66, 67);
	if (port.open() == -1) {
		Log::error("SPIPort.open() error");

		return -1;
	}
	Log::info("SPIPort.open() success");

// HX8357С
	port.writeByte(0xB9);	// Enable extension command
	port.writeByte(0xFF);
	port.writeByte(0x83);
	port.writeByte(0x57);
	usleep(50 * 1000);

	port.writeByte(0xB6);	//Set VCOM voltage
	port.writeByte(0x2C);	//0x52 for HSD 3.0"

	port.writeByte(0x11);	// Sleep off
	usleep(200 * 1000);

	port.writeByte(0x35);	// Tearing effect on
	port.writeByte(0x00);	// Added parameter

	port.writeByte(0x3A);	// Interface pixel format
	port.writeByte(0x55);	// 16 bits per pixel

	port.writeByte(0xB1);	// Power control
	port.writeByte(0x00);
	port.writeByte(0x15);
	port.writeByte(0x0D);
	port.writeByte(0x0D);
	port.writeByte(0x83);
	port.writeByte(0x48);

	port.writeByte(0xC0);	// Does this do anything?
	port.writeByte(0x24);
	port.writeByte(0x24);
	port.writeByte(0x01);
	port.writeByte(0x3C);
	port.writeByte(0xC8);
	port.writeByte(0x08);

	port.writeByte(0xB4);	// Display cycle
	port.writeByte(0x02);
	port.writeByte(0x40);
	port.writeByte(0x00);
	port.writeByte(0x2A);
	port.writeByte(0x2A);
	port.writeByte(0x0D);
	port.writeByte(0x4F);

	port.writeByte(0xE0); // Gamma curve
	port.writeByte(0x00);
	port.writeByte(0x15);
	port.writeByte(0x1D);
	port.writeByte(0x2A);
	port.writeByte(0x31);
	port.writeByte(0x42);
	port.writeByte(0x4C);
	port.writeByte(0x53);
	port.writeByte(0x45);
	port.writeByte(0x40);
	port.writeByte(0x3B);
	port.writeByte(0x32);
	port.writeByte(0x2E);
	port.writeByte(0x28);

	port.writeByte(0x24);
	port.writeByte(0x03);
	port.writeByte(0x00);
	port.writeByte(0x15);
	port.writeByte(0x1D);
	port.writeByte(0x2A);
	port.writeByte(0x31);
	port.writeByte(0x42);
	port.writeByte(0x4C);
	port.writeByte(0x53);
	port.writeByte(0x45);
	port.writeByte(0x40);
	port.writeByte(0x3B);
	port.writeByte(0x32);

	port.writeByte(0x2E);
	port.writeByte(0x28);
	port.writeByte(0x24);
	port.writeByte(0x03);
	port.writeByte(0x00);
	port.writeByte(0x01);

	port.writeByte(0x36); // MADCTL Memory access control
	port.writeByte(0x48);
	usleep(20 * 1000);

	port.writeByte(0x21); //Display inversion on
	usleep(20 * 1000);

	port.writeByte(0x29); // Display on
	usleep(120 * 1000);

	// try to draw red pixel
	port.writeByte(0x2A);
	port.writeByte(0x00);
	port.writeByte(0x10);
	port.writeByte(0x00);
	port.writeByte(0x10);
	port.writeByte(0x2B);
	port.writeByte(0x00);
	port.writeByte(0x10);
	port.writeByte(0x00);
	port.writeByte(0x10);
	port.writeByte(0x2C);
	port.writeByte(0xf8);
	port.writeByte(0x00);

	Log::info("Init success");

	if (port.close() == -1) {
		Log::error("SPIPort.close() error");

		return -1;
	}
	Log::info("SPIPort.close() success");

	return 0;
}
