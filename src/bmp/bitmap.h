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

class bitmap {
public:
	bitmapColorTable table;
	bitmapDIBHeader DIB;
	bitmapFileHeader fileHeader;
	bitmap();
	virtual ~bitmap();
};

#endif /* SRC_BMP_BITMAP_H_ */
