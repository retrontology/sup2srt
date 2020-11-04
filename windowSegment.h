/*
 * windowSegment.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef WINDOWSEGMENT_H_
#define WINDOWSEGMENT_H_

class windowSegment {
public:
	unsigned char windowID;
	unsigned int windowXPos;
	unsigned int windowYPos;
	unsigned int windowWidth;
	unsigned int windowHeight;
	windowSegment();
	windowSegment(char * windowID, char * windowXPos, char * windowYPos, char * windowWidth, char * windowHeight);
	virtual ~windowSegment();
};

#endif /* WINDOWSEGMENT_H_ */
