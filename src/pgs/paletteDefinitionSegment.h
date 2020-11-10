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
#include "../bmp/bitmapColorTable.h"
#include <vector>

class paletteDefinitionSegment: public pgsSegment {
public:
	unsigned char paletteID;
	unsigned char paletteVersionNumber;
	unsigned int paletteCount;
	std::vector<paletteSegment> paletteSegments;
	paletteDefinitionSegment(char * paletteID, char * paletteVersionNumber, std::vector<paletteSegment> paletteSegments, unsigned int paletteCount);
	virtual ~paletteDefinitionSegment();
	bitmapColorTable getColorTable();
};

#endif /* PALETTEDEFINITIONSEGMENT_H_ */
