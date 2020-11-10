/*
 * bitmapColorTable.h
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#ifndef SRC_BMP_BITMAPCOLORTABLE_H_
#define SRC_BMP_BITMAPCOLORTABLE_H_

#include <cstdint>

class bitmapColorTable {
public:
	unsigned long * colors;
	unsigned int length;
	bitmapColorTable(unsigned long * colors, unsigned int length);
	bitmapColorTable();
	virtual ~bitmapColorTable();
	void getByteArray(char * bytes);
};

#endif /* SRC_BMP_BITMAPCOLORTABLE_H_ */
