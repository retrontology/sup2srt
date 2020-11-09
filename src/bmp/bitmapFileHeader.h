/*
 * bitmapFileHeader.h
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#ifndef SRC_BMP_BITMAPFILEHEADER_H_
#define SRC_BMP_BITMAPFILEHEADER_H_

#define BITMAP_FILEHEADER_SIZE 14

enum fileHeader
{
	BM = 0x424D,
	BA = 0x4241,
	CI = 0x4349,
	CP = 0x4350,
	IC = 0x4943,
	PT = 0x5054
};

class bitmapFileHeader {
public:
	fileHeader header;
	unsigned long fileSize;
	unsigned int reserved1;
	unsigned int reserved2;
	unsigned long dataOffset;
	bitmapFileHeader(fileHeader header = BM, unsigned long fileSize = 0, unsigned int reserved1 = 0, unsigned int reserved2 = 0, unsigned long dataOffset = 0);
	virtual ~bitmapFileHeader();
};

#endif /* SRC_BMP_BITMAPFILEHEADER_H_ */
