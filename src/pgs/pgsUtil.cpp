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

void pgsUtil::decodeRLE(char * out, paletteDefinitionSegment pds, objectDefinitionSegment ods)
{
	unsigned int w = 0, h = 0;
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
							pixels[w][h] = pds.paletteSegments[0].getRGBA();
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
							pixels[w][h] = pds.paletteSegments[0].getRGBA();
							w++;
						}
						i+=2;
						break;
					}
					case 2:
					{
						for (unsigned char j = 0; j < pgsUtil::cleanChar(ods.data[i+1] & 0x3F); j++)
						{
							pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i+2])].getRGBA();
							w++;
						}
						i+=2;
						break;
					}
					case 3:
					{
						unsigned int count = pgsUtil::cleanChar(ods.data[i+2]) | pgsUtil::cleanChar(ods.data[i+1] & 0x3F) << 8;
						for(unsigned int j = 0; j < count; j++)
						{
							pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i+3])].getRGBA();
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
			pixels[w][h] = pds.paletteSegments[pgsUtil::cleanChar(ods.data[i])].getRGBA();
			w++;
		}
	}
}

