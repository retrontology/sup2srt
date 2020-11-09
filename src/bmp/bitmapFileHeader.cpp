/*
 * bitmapFileHeader.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#include "bitmapFileHeader.h"
#include <cstring>

bitmapFileHeader::bitmapFileHeader(fileHeader header, unsigned long fileSize, unsigned int reserved1, unsigned int reserved2, unsigned long dataOffset) {
	this->header = header;
	this->fileSize = fileSize;
	this->reserved1 = reserved1;
	this->reserved2 = reserved2;
	this->dataOffset = dataOffset;
}

bitmapFileHeader::~bitmapFileHeader()
{

}

void bitmapFileHeader::getByteArray(char * bytes)
{
	bitmapUtil::numToChars(bytes, this->header, 2);
	bitmapUtil::numToChars(bytes+2, this->fileSize, 4);
	bitmapUtil::numToChars(bytes+6, this->reserved1, 2);
	bitmapUtil::numToChars(bytes+8, this->reserved2, 2);
	bitmapUtil::numToChars(bytes+10, this->dataOffset, 4);
}

