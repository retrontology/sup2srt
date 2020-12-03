/*
 * paletteDefinitionSegment.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "paletteDefinitionSegment.h"
#include "pgsUtil.h"
#include "paletteSegment.h"
#include <memory>

paletteDefinitionSegment::paletteDefinitionSegment(char * paletteID, char * paletteVersionNumber, std::map<unsigned int, paletteSegment> paletteSegments, unsigned int paletteCount)
{
	this->paletteID = pgsUtil::cleanChar(paletteID[0]);
	this->paletteVersionNumber = pgsUtil::cleanChar(paletteVersionNumber[0]);
	this->paletteSegments = paletteSegments;
	this->paletteCount = paletteCount;
}

paletteDefinitionSegment::~paletteDefinitionSegment() {
	// TODO Auto-generated destructor stub
}

