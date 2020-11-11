/*
 * bitmapDIBHeaderV4.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: blazer
 */

#include "bitmapDIBHeaderV4.h"
#include "bitmapUtil.h"
#include <cstring>

bitmapDIBHeaderV4::bitmapDIBHeaderV4()
{

}

bitmapDIBHeaderV4::bitmapDIBHeaderV4( unsigned long width,
									  unsigned long height,
									  unsigned long imageSize,
									  unsigned long compression,
									  unsigned long colorCount,
									  unsigned int planes,
									  unsigned int bitsPerPixel,
									  unsigned long xppm,
									  unsigned long yppm,
									  unsigned long importantColorCount,
									  unsigned long redMask,
									  unsigned long greenMask,
									  unsigned long blueMask,
									  unsigned long alphaMask,
									  unsigned long colorSpaceType,
									  unsigned long long colorSpaceEndpoints,
									  unsigned long redGamma,
									  unsigned long greenGamma,
									  unsigned long blueGamma )
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

void bitmapDIBHeaderV4::getByteArray(char * bytes)
{
	bitmapUtil::numToChars(bytes, this->size, 4);
	bitmapUtil::numToChars(bytes+4, this->width, 4);
	bitmapUtil::numToChars(bytes+8, this->height, 4);
	bitmapUtil::numToChars(bytes+12, this->planes, 2);
	bitmapUtil::numToChars(bytes+14, this->bitsPerPixel, 2);
	bitmapUtil::numToChars(bytes+16, this->compression, 4);
	bitmapUtil::numToChars(bytes+20, this->imageSize, 4);
	bitmapUtil::numToChars(bytes+24, this->xppm, 4);
	bitmapUtil::numToChars(bytes+28, this->yppm, 4);
	bitmapUtil::numToChars(bytes+32, this->colorCount, 4);
	bitmapUtil::numToChars(bytes+36, this->importantColorCount, 4);
	bitmapUtil::numToChars(bytes+40, this->redMask, 4);
	bitmapUtil::numToChars(bytes+44, this->greenMask, 4);
	bitmapUtil::numToChars(bytes+48, this->blueMask, 4);
	bitmapUtil::numToChars(bytes+52, this->alphaMask, 4);
	bitmapUtil::numToChars(bytes+56, this->colorSpaceType, 4);
	//placeholder fo colorSpaceEndpoints
	bitmapUtil::numToChars(bytes+60, 0, 8);
	bitmapUtil::numToChars(bytes+68, 0, 8);
	bitmapUtil::numToChars(bytes+76, 0, 8);
	bitmapUtil::numToChars(bytes+84, 0, 8);
	bitmapUtil::numToChars(bytes+92, 0, 4);
	//end placeholder for colorSpaceEndpoints
	bitmapUtil::numToChars(bytes+96, this->size, 4);
	bitmapUtil::numToChars(bytes+100, this->size, 4);
	bitmapUtil::numToChars(bytes+104, this->size, 4);
}

