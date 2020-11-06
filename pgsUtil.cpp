/*
 * pgsUtil.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsUtil.h"
#include "pgsSegment.h"
#include "objectDefinitionSegment.h"
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

char * pgsUtil::subArray(char * ptr, int length, int start)
{
	char * temp = new char[length];
	int count = 0;
	for(int i = start; i < length+start; i++)
	{
		temp[count] = ptr[i];
		count++;
	}
	return temp;
};


/*void pgsUtil::dumpBMPs(std::vector<std::unique_ptr<pgsSegment> > segments)
{
	system("mkdir -p img");
	int count = 0;
	for(int i = 0; i < segments.size(); i++)
	{
		pgsSegment segment = *segments[i];
		if(segment.HEADER.SEGMENT_TYPE == ODS)
		{
			objectDefinitionSegment* segment = dynamic_cast<objectDefinitionSegment*>(segments[i].get());
			std::ostringstream ss;
			ss << std::setw(5) << std::setfill('0') << std::to_string(count);
			std::ofstream bmp("img/" + ss.str() + ".bmp");
			bmp.write(segment->data.data, segment->data.length);
			bmp.close();
			count++;
		}
	}
}*/


