/*
 * bitmapDIBHeaderV4.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: blazer
 */

#include "bitmapDIBHeaderV4.h"
#include <cstring>

bitmapDIBHeaderV4::bitmapDIBHeaderV4( unsigned long width,
									  unsigned long height,
									  unsigned int imageSize,
									  unsigned int colorCount,
									  unsigned char planes,
									  unsigned char bitsPerPixel,
									  unsigned int compression,
									  unsigned long xppm,
									  unsigned long yppm,
									  unsigned int importantColorCount,
									  unsigned int redMask,
									  unsigned int greenMask,
									  unsigned int blueMask,
									  unsigned int alphaMask,
									  unsigned int colorSpaceType,
									  unsigned long long colorSpaceEndpoints,
									  unsigned int redGamma,
									  unsigned int greenGamma,
									  unsigned int blueGamma )
{
	this->width = width;
	this->height = height;
	this->imageSize = imageSize;
	this->colorCount = colorCount;
	this->planes = planes;
	this->bitsPerPixel = bitsPerPixel;
	this->compression = compression;
	this->xppm = xppm;
	this->yppm = yppm;
	this->importantColorCount = importantColorCount;
	this->redMask = redMask;
	this->greenMask = greenMask;
	this->blueMask = blueMask;
	this->alphaMask = alphaMask;
	this->colorSpaceType = colorSpaceType;
	this->colorSpaceEndpoints = colorSpaceEndpoints;
	this->redGamma = redGamma;
	this->greenGamma = greenGamma;
	this->blueGamma = blueGamma;
	this->size = BITMAPV4HEADER;
}

bitmapDIBHeaderV4::~bitmapDIBHeaderV4() {
	// TODO Auto-generated destructor stub
}

unsigned char * bitmapDIBHeaderV4::getByteArray()
{
	unsigned char * bytes = new unsigned char[this->size];
	//std::memcpy();
	return bytes;
}

