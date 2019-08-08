/*
 * BMP.h
 *
 *  Created on: 7.08.2019
 *      Author: Potapov Sergei
 *       Email: sam-wanderman@yandex.ru
 */

#ifndef COURIERCXX_IMAGE_BMP_H_
#define COURIERCXX_IMAGE_BMP_H_

#include <cstdint>
#include <vector>

namespace Image {

/**
 * Class for BMP images
 */
class BMP {
public:
	/**
	 * BMP file header
	 */
#pragma pack(push, 1)
	struct FileHeader {
		uint16_t	type			{ 0x4D42 };
		uint32_t	size			{ 0 };
		uint16_t	reserved1		{ 0 };
		uint16_t	reserved2		{ 0 };
		uint32_t	offsetData		{ 0 };
	};
	typedef struct FileHeader FileHeader;
#pragma pack(pop)

	/**
	 * Info header
	 */
#pragma pack(push, 1)
	struct InfoHeader {
		uint32_t	size			{ 0 };
		int32_t		width			{ 0 };
		int32_t		height			{ 0 };
		uint16_t	planes			{ 1 };
		uint16_t	bitCount		{ 0 };
		uint32_t	compression		{ 0 };
		uint32_t	sizeImage		{ 0 };
		int32_t		xdpi			{ 0 };
		int32_t		ydpi			{ 0 };
		uint32_t	colorsUsed		{ 0 };
		uint32_t	colorsImportant	{ 0 };
	};
	typedef struct InfoHeader InfoHeader;
#pragma pack(pop)

	/**
	 * Color header
	 */
#pragma pack(push, 1)
	struct ColorHeader {
		uint32_t	redMask			{ 0x00ff0000 };
		uint32_t	greenMask		{ 0x0000ff00 };
		uint32_t	blueMask		{ 0x000000ff };
		uint32_t	alphaMask		{ 0xff000000 };
		uint32_t	colorspaceType	{ 0x73524742 };
		uint32_t	unused[16]		{ 0 };
	};
	typedef struct ColorHeader ColorHeader;
#pragma pack(pop)

	/**
	 * Constructor
	 *
	 * \param[in] uint32_t width - image width
	 * \param[in] uint32_t height - image height
	 * \param[in] uint32_t rowStride - row stride
	 * \param[in] const uint8_t* data - pointer to data
	 */
	BMP(uint32_t width, uint32_t height, uint32_t rowStride, const uint8_t* data);

	/**
	 * Destructor
	 */
	virtual ~BMP();

	/**
	 * Convert to bin
	 *
	 * \param[out] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max buffer size
	 *
	 * \return int - 0 if success, -1 if error
	 */
	int toBin(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Get total size
	 *
	 * \return int - image size if success, -1 if error
	 */
	int getTotalSize();

private:
	FileHeader fileHeader;
	InfoHeader infoHeader;
	ColorHeader colorHeader;
	std::vector<uint8_t> data;
	uint32_t rowStride = 0;

	/**
	 * Write headers to buffer
	 *
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max buffer size
	 *
	 * \return int - number of written bytes if success, -1 if error
	 */
	int writeHeaders(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Write headers and data to buffer
	 *
	 * \param[inout] uint8_t* buffer - pointer to buffer
	 * \param[in] uint32_t bufferSize - max buffer size
	 *
	 * \return int - number of written bytes if success, -1 if error
	 */
	int writeHeadersAndData(uint8_t* buffer, uint32_t bufferSize);

	/**
	 * Calc stride
	 *
	 * \param[in] uint32_t stride - stride
	 *
	 * \return uint32_t - aligned stride
	 */
	uint32_t makeStrideAligned(uint32_t stride);
};

} /* namespace Image */

#endif /* COURIERCXX_IMAGE_BMP_H_ */
