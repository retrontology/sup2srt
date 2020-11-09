/*
 * bitmapUtil.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#include "bitmapUtil.h"

void bitmapUtil::numToChars(char * out, unsigned long long num, unsigned int length)
{
	unsigned long long mask = 0x00000000000000FF;
	for(int i = 0; i < length; i++)
	{
		out[i] = (num & mask) >> (i*8);
		mask = mask << 8;
	}
}

