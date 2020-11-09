/*
 * presentationCompositionSegment.h
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#ifndef PRESENTATIONCOMPOSITIONSEGMENT_H_
#define PRESENTATIONCOMPOSITIONSEGMENT_H_

#include "pgsSegment.h"
#include "compositionObject.h"

class presentationCompositionSegment: public pgsSegment {
public:
	unsigned int width;
	unsigned int height;
	unsigned char framerate;
	unsigned int compNumber;
	unsigned char compState;
	unsigned char paletteUpdateFlag;
	unsigned char paletteID;
	unsigned char compObjectCount;
	compositionObject * compObjects;
	presentationCompositionSegment();
	presentationCompositionSegment(char * width, char * height, char * framerate, char * compNumber, char * compState, char * paletteUpdateFlag, char * paletteID, char * compObjectCount, compositionObject * compObjects);
	virtual ~presentationCompositionSegment();
};

#endif /* PRESENTATIONCOMPOSITIONSEGMENT_H_ */
