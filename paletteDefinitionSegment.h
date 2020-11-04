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

class paletteDefinitionSegment: public pgsSegment {
public:
	unsigned char paletteID;
	unsigned char paletteVersionNumber;
	unsigned int paletteCount;
	paletteSegment * paletteSegments;
	paletteDefinitionSegment(char * paletteID, char * paletteVersionNumber, paletteSegment * paletteSegments, unsigned int paletteCoun);
	virtual ~paletteDefinitionSegment();
};

#endif /* PALETTEDEFINITIONSEGMENT_H_ */
