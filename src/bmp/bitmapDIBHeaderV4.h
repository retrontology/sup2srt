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
	unsigned int planes;
	unsigned int bitsPerPixel;
	unsigned long compression;
	unsigned long imageSize;
	unsigned long xppm;
	unsigned long yppm;
	unsigned long colorCount;
	unsigned long importantColorCount;
	unsigned long redMask;
	unsigned long greenMask;
	unsigned long blueMask;
	unsigned long alphaMask;
	unsigned long colorSpaceType;
	unsigned long long colorSpaceEndpoints;
	unsigned long redGamma;
	unsigned long greenGamma;
	unsigned long blueGamma;
	bitmapDIBHeaderV4();
	bitmapDIBHeaderV4(unsigned long width,
					  unsigned long height,
					  unsigned long imageSize,
					  unsigned long compression = BI_RLE8,
					  unsigned long colorCount = 0,
					  unsigned int planes = 1,
					  unsigned int bitsPerPixel = 32,
					  unsigned long xppm = 2835,
					  unsigned long yppm = 2835,
					  unsigned long importantColorCount = 0,
					  unsigned long redMask = 0x000000FF,
					  unsigned long greenMask = 0x0000FF00,
					  unsigned long blueMask = 0x00FF0000,
					  unsigned long alphaMask = 0xFF000000,
					  unsigned long colorSpaceType = 0x42475273,
					  unsigned long long colorSpaceEndpoints = 0,
					  unsigned long redGamma = 0,
					  unsigned long greenGamma = 0,
					  unsigned long blueGamma = 0);
	virtual ~bitmapDIBHeaderV4();
	void getByteArray(char * bytes);
};

#endif /* SRC_BMP_BITMAPDIBHEADERV4_H_ */
