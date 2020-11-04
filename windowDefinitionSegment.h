/*
 * windowDefinitionSegment.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef WINDOWDEFINITIONSEGMENT_H_
#define WINDOWDEFINITIONSEGMENT_H_

#include "pgsSegment.h"
#include "windowSegment.h"

class windowDefinitionSegment: public pgsSegment  {
public:
	unsigned char numOfWindows;
	windowSegment * windowSegments;
	windowDefinitionSegment(char * numOfWindows, windowSegment * windowSegments);
	virtual ~windowDefinitionSegment();
};

#endif /* WINDOWDEFINITIONSEGMENT_H_ */
