/*
 * BMP.cpp
 *
 *  Created on: 7.08.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#include "BMP.h"

#include <algorithm>
#include <cstring>
#include <iterator>

#include "../logger/Log.h"

namespace Image {

BMP::BMP(uint32_t width, uint32_t height, uint32_t rowStride, const uint8_t* _data) {
	this->rowStride = rowStride;

	uint32_t bytesPerPixel = rowStride / width;

	fileHeader.offsetData = sizeof(FileHeader) + sizeof(InfoHeader);
	fileHeader.size = sizeof(FileHeader) + sizeof(InfoHeader) + height * (rowStride / bytesPerPixel * 4);

	// rows
	for (int i = height - 1; i >= 0; i--) {
		// pixels
		for (uint32_t j = 0; j < width; j++) {
			// colors
			for (uint32_t k = 0; k < bytesPerPixel; k++) {
				data.push_back(_data[k + j * bytesPerPixel + i * rowStride]);
			}
		}
	}
//	data = std::vector<uint8_t>(_data, _data + height * rowStride);

	infoHeader.size = sizeof(InfoHeader);
	infoHeader.bitCount = 24;
	infoHeader.width = width;
	infoHeader.height = height;
}

BMP::~BMP() { }

int BMP::toBin(uint8_t* buffer, uint32_t bufferSize) {
	if (infoHeader.bitCount == 32) {
		return writeHeadersAndData(buffer, bufferSize);
	} else if (infoHeader.bitCount == 24) {
		if (infoHeader.width % 4 == 0) {
			return writeHeadersAndData(buffer, bufferSize);
		} else {
			uint32_t newStride = makeStrideAligned(4);
			std::vector<uint8_t> paddingRow(newStride - rowStride);

			int idx = writeHeaders(buffer, bufferSize);
			if (idx == -1) {
				return -1;
			}

			for (int i = 0; i < infoHeader.height; i++) {
				memmove(&buffer[idx], data.data() + rowStride * i, rowStride);
				idx += rowStride;
				memmove(&buffer[idx], paddingRow.data(), paddingRow.size());
				idx += paddingRow.size();
			}

			Log::info("idx: %u", idx);

			return idx;
		}
	}

	return -1;
}

int BMP::writeHeaders(uint8_t* buffer, uint32_t bufferSize) {
	if (bufferSize < sizeof(fileHeader) + sizeof(infoHeader)) {
		return -1;
	}

	int idx = 0;
	memmove(&buffer[idx], &fileHeader, sizeof(fileHeader));
	idx += sizeof(fileHeader);
	memmove(&buffer[idx], &infoHeader, sizeof(infoHeader));
	idx += sizeof(infoHeader);

	if (infoHeader.bitCount == 32) {
		if (bufferSize < sizeof(fileHeader) + sizeof(infoHeader) + sizeof(colorHeader)) {
			return -1;
		}

		memmove(&buffer[idx], &colorHeader, sizeof(colorHeader));
		idx += sizeof(colorHeader);
	}

	return idx;
}

int BMP::writeHeadersAndData(uint8_t* buffer, uint32_t bufferSize) {
	int idx = writeHeaders(buffer, bufferSize);
	if (idx == -1) {
		return -1;
	}

	if (bufferSize < idx + data.size()) {
		return -1;
	}

	memmove(&buffer[idx], data.data(), data.size() * sizeof(uint8_t));

	return idx + data.size() + sizeof(uint8_t);
}

uint32_t BMP::makeStrideAligned(uint32_t stride) {
	uint32_t newStride = rowStride;
	while (newStride % stride != 0) {
		newStride++;
	}

	return newStride;
}

int BMP::getTotalSize() {
	return fileHeader.size;
}

} /* namespace Image */
