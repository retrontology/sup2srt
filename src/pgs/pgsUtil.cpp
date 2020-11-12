/*
 * pgsUtil.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsUtil.h"
#include "pgsSegment.h"
#include <iostream>
#include <bits/stdc++.h>
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

void pgsUtil::decodeRLE(unsigned long * out, paletteDefinitionSegment pds, objectDefinitionSegment ods)
{
	int w = 0;
	int h = 0;
	unsigned long pixels[ods.width][ods.height];
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
							pixels[w][h] = pds.paletteSegments[0].getARGB();
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
							pixels[w][h] = pds.paletteSegments[0].getARGB();
							w++;
						}
						i+=2;
						break;
					}
					case 2:
					{
						for (unsigned char j = 0; j < pgsUtil::cleanChar(ods.data[i+1] & 0x3F); j++)
						{
							pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i+2])].getARGB();
							w++;
						}
						i+=2;
						break;
					}
					case 3:
					{
						unsigned int count = pgsUtil::cleanChar(ods.data[i+2]) | (pgsUtil::cleanChar(ods.data[i+1] & 0x3F) << 8);
						for(unsigned int j = 0; j < count; j++)
						{
							pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i+3])].getARGB();
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
			pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i])].getARGB();
			w++;
		}
	}
	unsigned long count = 0;
	for(h = ods.height - 1; h >= 0; h--)
	{
		for(w=0; w < ods.width; w++)
		{
			out[count] = pixels[w][h];
			count++;
		}
	}
}

