#include "../couriercxx/image/JPG.h"

#include <cstdint>
#include <cstdlib>
#include <string>

#include "../couriercxx/logger/Log.h"
#include "../couriercxx/util/IO.h"

int main(int ac, char** av) {
	Log::setAppName(&av[0][2]);

	if (ac < 6) {
		Log::info("Usage %s width height bytes_per_pixel in_file_name out_file_name", &av[0][2]);

		return 0;
	}

	// 155 75 3
	uint32_t width = atoi(av[1]);
	uint32_t height = atoi(av[2]);
	uint8_t bytesPerPixel = atoi(av[3]);

	int bufferSize = IO::getSize(std::string(av[4]));
	if (bufferSize == -1) {
		Log::error("IO.getSize() error");

		return 0;
	}

	uint8_t* buffer = new uint8_t[bufferSize];
	int readBytes = IO::readFrom(std::string(av[4]), buffer, bufferSize);
	if (readBytes == -1) {
		Log::error("IO.readFrom() error");

		delete[] buffer;

		return -1;
	}
	Log::debug("IO.readFrom() read %u bytes", readBytes);

	Image::JPG* jpg = new Image::JPG(width, height, bytesPerPixel, buffer);

	delete[] buffer;

	uint8_t* outBuffer = nullptr;
	uint64_t outBufferSize = 0;
	if (jpg->toBin(&outBuffer, &outBufferSize) == -1) {
		Log::error("JPG.toBin() error");
	} else {
		Log::info("JPG.toBin() success");
	}

	delete jpg;

	if (IO::writeTo(av[5], outBuffer, outBufferSize) == -1) {
		Log::error("IO.writeTo() error");

		delete[] outBuffer;

		return -1;
	}
	Log::debug("IO.writeTo() success");

	delete[] outBuffer;

	return 0;
}
