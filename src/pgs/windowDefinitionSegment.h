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
#include <vector>

class windowDefinitionSegment: public pgsSegment  {
public:
	unsigned char numOfWindows;
	std::vector<windowSegment> windowSegments;
	windowDefinitionSegment(char * numOfWindows, std::vector<windowSegment> windowSegments);
	virtual ~windowDefinitionSegment();
};

#endif /* WINDOWDEFINITIONSEGMENT_H_ */
