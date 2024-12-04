/*
 * pgsUtil.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsUtil.h"
#include "pgsSegment.h"
#include <iostream>
#include <fstream>

unsigned long int pgsUtil::char4ToLong(char * ptr)
{
	return cleanChar(ptr[3]) | (cleanChar(ptr[2]) << 8) | (cleanChar(ptr[1]) << 16) | (cleanChar(ptr[0]) << 24);
};

unsigned long int pgsUtil::char3ToLong(char * ptr)
{
	return cleanChar(ptr[2]) | (cleanChar(ptr[1]) << 8) | (cleanChar(ptr[0]) << 16);
};

unsigned int pgsUtil::char2ToInt(char * ptr)
{
	return cleanChar(ptr[1]) | (cleanChar(ptr[0]) << 8);
};

unsigned char pgsUtil::cleanChar(char in)
{
	return static_cast<unsigned int>(in) ;
};

double pgsUtil::ptsToMilli(unsigned long in)
{
	return double(in/90);
}

void pgsUtil::decodeRLE(unsigned long ** pixels, paletteDefinitionSegment pds, objectDefinitionSegment ods, bool gray)
{
	int w = 0, h = 0;
	for(int i = 0; i < ods.objectDataLength; i++)
	{
		if(ods.data[i] == 0x00)
		{
			// End of line
			if(ods.data[i+1] == 0x00)
			{
				h++;
				w=0;
				if(ods.height == h) { break; }
				i+=1;
			}
			else
			{
				switch((ods.data[i+1] & 0xC0) >> 6)
				{
					case 0:
					{
						for(unsigned char j = 0; j < pgsUtil::cleanChar(ods.data[i+1]); j++)
						{
							if(gray) pixels[h][w] = pds.paletteSegments[0].gray;
							else pixels[h][w] = pds.paletteSegments[0].getARGB();
							w++;
						}
						i+=1;
						break;
					}
					case 1:
					{
						unsigned int count = pgsUtil::cleanChar(ods.data[i+2]) | pgsUtil::cleanChar(ods.data[i+1] & 0x3F) << 8;
						for(unsigned int j = 0; j < count; j++)
						{
							if(gray) pixels[h][w] = pds.paletteSegments[0].gray;
							else pixels[h][w] = pds.paletteSegments[0].getARGB();
							w++;
						}
						i+=2;
						break;
					}
					case 2:
					{
						unsigned char color = pgsUtil::cleanChar(ods.data[i+2]);
						for (unsigned char j = 0; j < pgsUtil::cleanChar(ods.data[i+1] & 0x3F); j++)
						{

							if(gray) pixels[h][w] = pds.paletteSegments[color].gray;
							else pixels[h][w] = pds.paletteSegments[color].getARGB();
							w++;
						}
						i+=2;
						break;
					}
					case 3:
					{
						unsigned int count = pgsUtil::cleanChar(ods.data[i+2]) | (pgsUtil::cleanChar(ods.data[i+1] & 0x3F) << 8);
						unsigned char color = pgsUtil::cleanChar(ods.data[i+3]);
						for(unsigned int j = 0; j < count; j++)
						{
							if(gray) pixels[h][w] = pds.paletteSegments[color].gray;
							else pixels[h][w] = pds.paletteSegments[color].getARGB();
							w++;
						}
						i+=3;
						break;
					}
				}
			}
		}
		else
		{
			unsigned char color = pgsUtil::cleanChar(ods.data[i]);
			if(gray) pixels[h][w] = pds.paletteSegments[color].gray;
			else pixels[h][w] = pds.paletteSegments[color].getARGB();
			w++;
		}
		//if(invert) pixels[h][w] = pgsUtil::invertColor(pixels[h][w], 3);
	}
}

void pgsUtil::numToChars(char * out, unsigned long long num, unsigned int length)
{
	unsigned long long mask = 0x00000000000000FF;
	for(int i = 0; i < length; i++)
	{
		out[i] = (num & mask) >> (i*8);
		mask = mask << 8;
	}
}

unsigned long pgsUtil::invertColor(unsigned long color, char alphaOffset)
{
	unsigned long invert = 0x00000000;
	for (int i = 0; i < 4; i++)
	{
		if(i != alphaOffset)
		{
			unsigned long channel = 0x00000000;
			channel = (255 << (i*8)) - (color & (0x000000FF << (i*8)));
			invert = invert | channel;
		}
	}
	return invert;
}

