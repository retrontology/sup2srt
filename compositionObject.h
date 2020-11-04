/*
 * compositionObject.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef COMPOSITIONOBJECT_H_
#define COMPOSITIONOBJECT_H_

class compositionObject {
public:
	unsigned int objectID;
	unsigned char windowID;
	unsigned char objectCroppedFlag;
	unsigned int objectXPos;
	unsigned int objectYPos;
	unsigned int objectCropXPos;
	unsigned int objectCropYPos;
	unsigned int objectCropWidth;
	unsigned int objectCropHeight;
	compositionObject();
	compositionObject(char * objectID, char * windowID, char * objectCroppedFlag, char * objectXPos, char * objectYPos, char * objectCropXPos, char * objectCropYPos, char * objectCropWidth, char * objectCropHeight);
	virtual ~compositionObject();
};

#endif /* COMPOSITIONOBJECT_H_ */
