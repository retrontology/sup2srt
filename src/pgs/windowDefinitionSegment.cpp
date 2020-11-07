/*
 * windowDefinitionSegment.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "windowDefinitionSegment.h"
#include "pgsUtil.h"
#include "windowSegment.h"

windowDefinitionSegment::windowDefinitionSegment(char * numOfWindows, windowSegment * windowSegments) {
	// TODO Auto-generated constructor stub
	this->numOfWindows = pgsUtil::cleanChar(numOfWindows[0]);
	this->windowSegments = windowSegments;
}

windowDefinitionSegment::~windowDefinitionSegment() {
	// TODO Auto-generated destructor stub
}

