/*
 * bitmap.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#include "bitmap.h"
#include <cstring>

bitmap::bitmap(bitmapFileHeader fileHeader, bitmapDIBHeaderV4 DIB, bitmapColorTable table, char * data) {
	this->fileHeader = fileHeader;
	this->DIB = DIB;
	this->table = table;
	this->data = new char[this->DIB.imageSize];
	memcpy(this->data, data, this->DIB.imageSize);
}

bitmap::~bitmap() {
	// TODO Auto-generated destructor stub
}

