/*
 * bitmapFileHeader.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#include "bitmapFileHeader.h"

bitmapFileHeader::bitmapFileHeader(fileHeader header, unsigned long fileSize, unsigned int reserved1, unsigned int reserved2, unsigned long dataOffset) {
	this->header = header;
	this->fileSize = fileSize;
	this->reserved1 = reserved1;
	this->reserved2 = reserved2;
	this->dataOffset = dataOffset;
}

bitmapFileHeader::~bitmapFileHeader() {
	// TODO Auto-generated destructor stub
}

