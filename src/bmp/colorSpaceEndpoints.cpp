/*
 * colorSpaceEndpoints.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#include "colorSpaceEndpoints.h"
#include "bitmapUtil.h"
#include <cstring>

colorSpaceEndpoints::colorSpaceEndpoints(long long r, long long g, long long b) {
	this->r = new char[12];
	this->g = new char[12];
	this->b = new char[12];
}

colorSpaceEndpoints::~colorSpaceEndpoints() {
	// TODO Auto-generated destructor stub
}

