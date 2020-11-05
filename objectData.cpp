/*
 * objectData.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "objectData.h"

objectData::objectData()
{
	this->data = nullptr;
	this->length = -1;
}

objectData::objectData(char * data, long length)
{
	this->data = data;
	this->length = length;
}

objectData::~objectData() {
	// TODO Auto-generated destructor stub
}

