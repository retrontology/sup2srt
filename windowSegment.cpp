/*
 * windowSegment.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "windowSegment.h"
#include "pgsUtil.h"

windowSegment::windowSegment()
{
	this->windowID = -1;
	this->windowXPos = -1;
	this->windowYPos = -1;
	this->windowWidth = -1;
	this->windowHeight = -1;
}

windowSegment::windowSegment(char * windowID, char * windowXPos, char * windowYPos, char * windowWidth, char * windowHeight) {
	this->windowID = pgsUtil::cleanChar(windowID[0]);
	this->windowXPos = pgsUtil::char2ToInt(windowXPos);
	this->windowYPos = pgsUtil::char2ToInt(windowYPos);
	this->windowWidth = pgsUtil::char2ToInt(windowWidth);
	this->windowHeight = pgsUtil::char2ToInt(windowHeight);
}

windowSegment::~windowSegment() {
	// TODO Auto-generated destructor stub
}

