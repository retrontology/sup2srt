/*
 * bitmapColorTable.cpp
 *
 *  Created on: Nov 7, 2020
 *      Author: blazer
 */

#include "bitmapColorTable.h"

bitmapColorTable::bitmapColorTable(unsigned long * colors, unsigned int length)
{
	this->colors = new unsigned int[length];
	for(int i = 0; i < length; i ++) { this->colors[i] = colors[i]; }
	this->length = length;
}

bitmapColorTable::bitmapColorTable()
{
	this->colors = nullptr;
	this->length = 0;
}

bitmapColorTable::~bitmapColorTable() {
	// TODO Auto-generated destructor stub
}

