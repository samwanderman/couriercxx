#include "../couriercxx/image/BMP.h"

#include <cstdint>
#include <string>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/util/IO.h"

#define HEIGHT	75
#define WIDTH	155
#define STRIDE	465

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 2) {
		Log::info("Usage %s file_name", &av[0][2]);

		return 0;
	}

	int size = IO::getSize(std::string(av[1]));
	if (size == -1) {
		Log::error("IO.getSize() error");

		return 0;
	}

	uint8_t* buffer = new uint8_t[size];
	int res = IO::readFrom(std::string(av[1]), buffer, size);
	if (res == -1) {
		Log::error("IO.readFrom() error");

		delete[] buffer;

		return -1;
	}
	Log::debug("IO.readFrom() read %u bytes", res);

	Image::BMP* img = new Image::BMP(WIDTH, HEIGHT, STRIDE, buffer);
	delete[] buffer;

	size = img->getTotalSize();
	Log::info("Total image size is %u", size);
	buffer = new uint8_t[size];

	if ((size = img->toBin(buffer, size)) == -1) {
		Log::error("BMP.toBin() error");

		delete[] buffer;

		return -1;
	}
	Log::debug("converted size: %u", size);

	if (IO::writeTo("out.bmp", buffer, size) == -1) {
		Log::error("IO.writeTo() error");

		delete[] buffer;

		return -1;
	}
	Log::debug("IO.writeTo() success");

	delete[] buffer;

	return 0;
}
