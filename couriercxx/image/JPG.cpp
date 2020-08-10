/*
 * JPG.cpp
 *
 *  Created on: 26.08.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "JPG.h"

#ifndef _WIN32

#include <cstdio>
#include <cstdlib>
#include <jpeglib.h>
#include <cstring>

namespace Image {

JPG::JPG(uint32_t width, uint32_t height, uint32_t bytesPerPixel, const uint8_t* data) {
	this->width = width;
	this->height = height;
	this->bytesPerPixel = bytesPerPixel;

	uint64_t totalSize = width * bytesPerPixel * height;
	this->data = new uint8_t[totalSize];
	memmove(this->data, data, totalSize * sizeof(uint8_t));

	for (uint64_t i = 0; i < totalSize; i += this->bytesPerPixel) {
		int tmp = this->data[i] + this->data[i + 2];
		this->data[i] = this->data[i + 2];
		this->data[i + 2] = tmp - this->data[i + 2];
	}
}

JPG::JPG(uint32_t width, uint32_t height, uint32_t bytesPerPixel, const uint8_t* data, uint8_t quality) : JPG(width, height, bytesPerPixel, data) {
	this->quality = quality;
}

JPG::~JPG() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

int JPG::toBin(uint8_t** outBuffer, uint64_t* outBufferSize) {
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	jpeg_mem_dest(&cinfo, outBuffer, static_cast<unsigned long*>(outBufferSize));

	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = bytesPerPixel;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, true);
	jpeg_start_compress(&cinfo, true);

	JSAMPROW rowPointer[1];

	uint64_t rowStride = width * bytesPerPixel;
	while (cinfo.next_scanline < cinfo.image_height) {
		rowPointer[0] = &data[cinfo.next_scanline * rowStride];
		jpeg_write_scanlines(&cinfo, rowPointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	return 0;
}

} /* namespace Image */

#endif
