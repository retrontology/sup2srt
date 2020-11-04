/*
 * paletteSegment.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "paletteSegment.h"
#include "pgsUtil.h"

paletteSegment::paletteSegment()
{
	this->paletteEntryID = -1;
	this->luminance = -1;
	this->colorDiffRed = -1;
	this->colorDiffBlue = -1;
	this->transparency = -1;
}

paletteSegment::paletteSegment(char * paletteEntryID, char * luminance, char * colorDiffRed, char * colorDiffBlue, char * transparency)
{
	this->paletteEntryID = pgsUtil::cleanChar(paletteEntryID[0]);
	this->luminance = pgsUtil::cleanChar(luminance[0]);
	this->colorDiffRed = pgsUtil::cleanChar(colorDiffRed[0]);
	this->colorDiffBlue = pgsUtil::cleanChar(colorDiffBlue[0]);
	this->transparency = pgsUtil::cleanChar(transparency[0]);
}

paletteSegment::~paletteSegment() {
	// TODO Auto-generated destructor stub
}

