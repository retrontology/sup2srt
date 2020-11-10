/*
 * objectDefinitionSegment.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef OBJECTDEFINITIONSEGMENT_H_
#define OBJECTDEFINITIONSEGMENT_H_

#include "pgsSegment.h"

class objectDefinitionSegment: public pgsSegment {
public:
	unsigned int objectID;
	unsigned char objectVersionNumber;
	unsigned char lastInSequenceFlag;
	unsigned long objectDataLength;
	unsigned int width;
	unsigned int height;
	char * data;
	objectDefinitionSegment(char * objectID, char * objectVersionNumber, char * lastInSequenceFlag, char * objectDataLength, char * width, char * height, char * data);
	virtual ~objectDefinitionSegment();
};

#endif /* OBJECTDEFINITIONSEGMENT_H_ */
