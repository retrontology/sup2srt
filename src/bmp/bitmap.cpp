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

void bitmap::getByteArray(char * bytes)
{
	this->fileHeader.getByteArray(bytes);
	this->DIB.getByteArray(bytes+BITMAP_FILEHEADER_SIZE);
	this->table.getByteArray(bytes+BITMAP_FILEHEADER_SIZE+this->DIB.size);
	memcpy(bytes+BITMAP_FILEHEADER_SIZE+this->DIB.size+this->table.length*4, this->data, this->fileHeader.fileSize);
}

