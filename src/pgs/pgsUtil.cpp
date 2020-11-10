/*
 * pgsUtil.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsUtil.h"
#include "pgsSegment.h"
#include "objectDefinitionSegment.h"
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

unsigned long int pgsUtil::char4ToLong(char * ptr)
{
	return cleanChar(ptr[3]) | (cleanChar(ptr[2]) << 8) | (cleanChar(ptr[1]) << 16) | (cleanChar(ptr[0]) << 24);
};

unsigned long int pgsUtil::char3ToLong(char * ptr)
{
	return cleanChar(ptr[2]) | (cleanChar(ptr[1]) << 8) | (cleanChar(ptr[0]) << 16);
};

unsigned int pgsUtil::char2ToInt(char * ptr)
{
	return cleanChar(ptr[1]) | (cleanChar(ptr[0]) << 8);
};

unsigned char pgsUtil::cleanChar(char in)
{
	return static_cast<unsigned int>(in) ;
};

