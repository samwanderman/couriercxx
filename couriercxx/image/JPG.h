/*
 * JPG.h
 *
 *  Created on: 26.08.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_IMAGE_JPG_H_
#define COURIERCXX_IMAGE_JPG_H_

#include <cstdint>

namespace Image {

const uint8_t DEFAULT_QUALITY = 90;

/**
 * Class for JPG images
 */
class JPG {
public:
	/**
	 * Constructor
	 *
	 * \param[in] uint32_t width - image width
	 * \param[in] uint32_t height - image height
	 * \param[in] uint32_t bytesPerPixel - bytes per pixel
	 * \param[in] const uint8_t* data - pointer to data
	 */
	JPG(uint32_t width, uint32_t height, uint32_t bytesPerPixel, const uint8_t* data);

	/**
	 * Constructor
	 *
	 * \param[in] uint32_t width - image width
	 * \param[in] uint32_t height - image height
	 * \param[in] uint32_t bytesPerPixel - bytes per pixel
	 * \param[in] const uint8_t* data - pointer to data
	 * \param[in] uint8_t quality - resulting image quality
	 */
	JPG(uint32_t width, uint32_t height, uint32_t bytesPerPixel, const uint8_t* data, uint8_t quality);

	/**
	 * Destructor
	 */
	virtual ~JPG();

	/**
	 * Convert to bin
	 *
	 * \param[out] uint8_t** buffer - pointer to pointer to buffer
	 * \param[in] uint64_t* bufferSize - pointer to buffer size
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int toBin(uint8_t** outBuffer, uint64_t* outBufferSize);

private:
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t bytesPerPixel = 0;
	uint8_t quality = DEFAULT_QUALITY;
	uint8_t* data = nullptr;
};

} /* namespace Image */

#endif /* COURIERCXX_IMAGE_JPG_H_ */
