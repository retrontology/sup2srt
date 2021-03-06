/*
 * paletteSegment.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef PALETTESEGMENT_H_
#define PALETTESEGMENT_H_

class paletteSegment {
private:
	unsigned char calcRed(unsigned char Y, unsigned char Cb, unsigned char Cr);
	unsigned char calcGreen(unsigned char Y, unsigned char Cb, unsigned char Cr);
	unsigned char calcBlue(unsigned char Y, unsigned char Cb, unsigned char Cr);
	unsigned long calcGray(unsigned char transparency, unsigned char luminance);
public:
	unsigned char paletteEntryID;
	unsigned char luminance;
	unsigned char colorDiffRed;
	unsigned char colorDiffBlue;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char transparency;
	unsigned long gray;
	unsigned long getRGBA();
	unsigned long getARGB();
	unsigned long getABGR();
	paletteSegment();
	paletteSegment(char * paletteEntryID, char * luminance, char * colorDiffRed, char * colorDiffBlue, char * transparency);
	virtual ~paletteSegment();
};

#endif /* PALETTESEGMENT_H_ */
