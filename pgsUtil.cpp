/*
 * pgsUtil.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsUtil.h"
#include <iostream>

unsigned long int char4ToLong(char * ptr)
{
	return cleanChar(ptr[3]) | (cleanChar(ptr[2]) << 8) | (cleanChar(ptr[1]) << 16) | (cleanChar(ptr[0]) << 24);
};

unsigned int char2ToLong(char * ptr)
{
	return cleanChar(ptr[1]) | (cleanChar(ptr[0]) << 8);
};

unsigned char cleanChar(char in)
{
	return static_cast<unsigned int>(in) ;
}

