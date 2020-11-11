/*
 * bitmap.h
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#ifndef SRC_BMP_BITMAP_H_
#define SRC_BMP_BITMAP_H_

#include "bitmapColorTable.h"
#include "bitmapDIBHeader.h"
#include "bitmapFileHeader.h"
#include "bitmapDIBHeaderV4.h"

class bitmap {
public:
	bitmapColorTable table;
	bitmapDIBHeaderV4 DIB;
	bitmapFileHeader fileHeader;
	char * data;
	bitmap(bitmapFileHeader fileHeader, bitmapDIBHeaderV4 DIB, char * data, bitmapColorTable table = bitmapColorTable());
	virtual ~bitmap();
	void getByteArray(char * bytes);
};

#endif /* SRC_BMP_BITMAP_H_ */
