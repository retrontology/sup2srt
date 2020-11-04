/*
 * presentationCompositionSegment.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "presentationCompositionSegment.h"
#include "pgsUtil.h"
#include "compositionObject.h"

presentationCompositionSegment::presentationCompositionSegment(char * width, char * height, char * framerate, char * compNumber, char * paletteUpdateFlag, char * paletteID, char * compObjectCount, compositionObject * compObjects)
{
	this->width = pgsUtil::char2ToInt(width);
	this->height = pgsUtil::char2ToInt(height);
	this->framerate = pgsUtil::cleanChar(framerate[0]);
	this->compNumber = pgsUtil::char2ToInt(compNumber);
	this->paletteUpdateFlag = pgsUtil::cleanChar(paletteUpdateFlag[0]);
	this->paletteID = pgsUtil::cleanChar(paletteID[0]);
	this->compObjectCount = pgsUtil::cleanChar(compObjectCount[0]);
	this->compObjects = compObjects;
}

presentationCompositionSegment::~presentationCompositionSegment()
{
	// TODO Auto-generated destructor stub
}

