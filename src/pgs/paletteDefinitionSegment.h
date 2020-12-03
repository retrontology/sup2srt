/*
 * paletteDefinitionSegment.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef PALETTEDEFINITIONSEGMENT_H_
#define PALETTEDEFINITIONSEGMENT_H_
#include "pgsSegment.h"
#include "paletteSegment.h"
#include <map>

class paletteDefinitionSegment: public pgsSegment {
public:
	unsigned char paletteID;
	unsigned char paletteVersionNumber;
	unsigned int paletteCount;
	std::map<unsigned int, paletteSegment> paletteSegments;
	paletteDefinitionSegment(char * paletteID, char * paletteVersionNumber, std::map<unsigned int, paletteSegment> paletteSegments, unsigned int paletteCount);
	virtual ~paletteDefinitionSegment();
};

#endif /* PALETTEDEFINITIONSEGMENT_H_ */
