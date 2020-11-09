/*
 * compositionObject.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#include "compositionObject.h"
#include "pgsUtil.h"

compositionObject::compositionObject()
{
	this->objectID = 0;
	this->windowID = 0;
	this->objectCroppedFlag = 0;
	this->objectXPos = 0;
	this->objectYPos = 0;
	this->objectCropXPos = 0;
	this->objectCropYPos = 0;
	this->objectCropWidth = 0;
	this->objectCropHeight = 0;
}

compositionObject::compositionObject(char * objectID, char * windowID, char * objectCroppedFlag, char * objectXPos, char * objectYPos, char * objectCropXPos, char * objectCropYPos, char * objectCropWidth, char * objectCropHeight)
{
	this->objectID = pgsUtil::char2ToInt(objectID);
	this->windowID = pgsUtil::cleanChar(windowID[0]);
	this->objectCroppedFlag = pgsUtil::cleanChar(objectCroppedFlag[0]);
	this->objectXPos = pgsUtil::char2ToInt(objectXPos);
	this->objectYPos = pgsUtil::char2ToInt(objectYPos);
	this->objectCropXPos = pgsUtil::char2ToInt(objectCropXPos);
	this->objectCropYPos = pgsUtil::char2ToInt(objectCropYPos);
	this->objectCropWidth = pgsUtil::char2ToInt(objectCropWidth);
	this->objectCropHeight = pgsUtil::char2ToInt(objectCropHeight);
}

compositionObject::compositionObject(char * objectID, char * windowID, char * objectCroppedFlag, char * objectXPos, char * objectYPos)
{
	this->objectID = pgsUtil::char2ToInt(objectID);
	this->windowID = pgsUtil::cleanChar(windowID[0]);
	this->objectCroppedFlag = pgsUtil::cleanChar(objectCroppedFlag[0]);
	this->objectXPos = pgsUtil::char2ToInt(objectXPos);
	this->objectYPos = pgsUtil::char2ToInt(objectYPos);
	this->objectCropXPos = 0;
	this->objectCropYPos = 0;
	this->objectCropWidth = 0;
	this->objectCropHeight = 0;
}

compositionObject::~compositionObject()
{
	// TODO Auto-generated destructor stub
}

