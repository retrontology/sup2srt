/*
 * bitmapDIBHeaderV4.h
 *
 *  Created on: Nov 8, 2020
 *      Author: blazer
 */

#ifndef SRC_BMP_BITMAPDIBHEADERV4_H_
#define SRC_BMP_BITMAPDIBHEADERV4_H_

#include "bitmapDIBHeader.h"

class bitmapDIBHeaderV4: public bitmapDIBHeader {
public:
	unsigned long width;
	unsigned long height;
	unsigned char planes;
	unsigned char bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned long xppm;
	unsigned long yppm;
	unsigned int colorCount;
	unsigned int importantColorCount;
	unsigned int redMask;
	unsigned int greenMask;
	unsigned int blueMask;
	unsigned int alphaMask;
	unsigned int colorSpaceType;
	unsigned long long colorSpaceEndpoints;
	unsigned int redGamma;
	unsigned int greenGamma;
	unsigned int blueGamma;
	bitmapDIBHeaderV4(unsigned long width,
					  unsigned long height,
					  unsigned int imageSize,
					  unsigned int colorCount = 0,
					  unsigned char planes = 1,
					  unsigned char bitsPerPixel = 32,
					  unsigned int compression = BI_RLE8,
					  unsigned long xppm = 2835,
					  unsigned long yppm = 2835,
					  unsigned int importantColorCount = 0,
					  unsigned int redMask = 0,
					  unsigned int greenMask = 0,
					  unsigned int blueMask = 0,
					  unsigned int alphaMask = 0,
					  unsigned int colorSpaceType = 0x73524742,
					  unsigned long long colorSpaceEndpoints = 0,
					  unsigned int redGamma = 0,
					  unsigned int greenGamma = 0,
					  unsigned int blueGamma = 0);
	virtual ~bitmapDIBHeaderV4();
	unsigned char * getByteArray();
};

#endif /* SRC_BMP_BITMAPDIBHEADERV4_H_ */
