/*
 * pgsParser.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */

#include <fstream>
#include <bits/stdc++.h>
#include <tesseract/baseapi.h>
#include <libavcodec/avcodec.h>
#include <string>
#include <stdlib.h>
#include "pgsUtil.h"
#include "pgsParser.h"
#include "pgsSegment.h"
#include "pgsSegmentHeader.h"
#include "presentationCompositionSegment.h"
#include "compositionObject.h"
#include "windowDefinitionSegment.h"
#include "windowSegment.h"
#include "paletteDefinitionSegment.h"
#include "objectDefinitionSegment.h"
#include "objectData.h"

pgsParser::pgsParser(std::string filename)
{
	this->open(filename);

};

pgsParser::pgsParser(){};

pgsParser::~pgsParser()
{
	if (this->pgsData.is_open()) { this->pgsData.close(); }
};

void pgsParser::open(std::string filename)
{
	this->pgsData.open(filename, std::ifstream::binary);
	this->parseAllSegments();
};

pgsSegment pgsParser::parseNextSegment()
{
	char * buffer = new char [13];
	this->pgsData.read(buffer, 13);
	pgsSegmentHeader header = this->parseHeader(buffer);
	pgsSegment segment;
	buffer = new char[header.SEGMENT_SIZE];
	if(header.SEGMENT_SIZE > 0) { this->pgsData.read(buffer, header.SEGMENT_SIZE); }
	switch (header.SEGMENT_TYPE)
	{
		case PDS :
		{
			segment = this->parsePDS(buffer, header.SEGMENT_SIZE);
			break;
		}
		case ODS :
		{
			segment = this->parseODS(buffer, header.SEGMENT_SIZE);
			break;
		}
		case PCS :
		{
			segment = this->parsePCS(buffer, header.SEGMENT_SIZE);
			break;
		}
		case WDS :
		{
			segment = this->parseWDS(buffer, header.SEGMENT_SIZE);
			break;
		}
		case END :
		{
			std::cout << "Reached end of stream :D" << std::endl;
			segment = pgsSegment();
			break;
		}
		case ERR :
		{
			std::cout << "Failed to find magic number. Either stream is corrupt or you dun fukt up son :|" << std::endl;
			exit (EXIT_FAILURE);
			break;
		}
	}
	segment.HEADER = header;
	return segment;

};

pgsSegmentHeader pgsParser::parseHeader(char * buffer)
{
	// Check for magic number
	std::string magicNumber (pgsUtil::subArray(buffer, 2));
	if (magicNumber == "PG")
	{
		// Read Header
		char * pts = pgsUtil::subArray(buffer, 4, 2);
		char * dts = pgsUtil::subArray(buffer, 4, 6);
		char * type = pgsUtil::subArray(buffer, 1, 10);
		char * size = pgsUtil::subArray(buffer, 2, 11);
		return pgsSegmentHeader(pts, dts, type, size);
	}
	else
	{
		return pgsSegmentHeader();
	}

}

presentationCompositionSegment pgsParser::parsePCS(char * buffer, unsigned int segmentSize)
{
	char * width = pgsUtil::subArray(buffer, 2);
	char * height = pgsUtil::subArray(buffer, 2, 2);
	char * framerate = pgsUtil::subArray(buffer, 1, 4);
	char * compNumber = pgsUtil::subArray(buffer, 2, 5);
	char * compState = pgsUtil::subArray(buffer, 1, 7);
	char * paletteUpdateFlag = pgsUtil::subArray(buffer, 1, 8);
	char * paletteID = pgsUtil::subArray(buffer, 1, 9);
	char * compObjectCount = pgsUtil::subArray(buffer, 1, 10);
	unsigned int count = pgsUtil::cleanChar(compObjectCount[0]);
	compositionObject * compObjects = new compositionObject[count];
	unsigned int offset = 11;
	// Parse Objects
	for(int i = 0; i < count; i++)
	{
		// Read only first 4 so we know how big the object is before reading the rest
		char * objID = pgsUtil::subArray(buffer, 2, offset);
		char * windowID = pgsUtil::subArray(buffer, 1, offset+2);
		char * objCropFlag = pgsUtil::subArray(buffer, 1, offset+3);
		char * objXPos = pgsUtil::subArray(buffer, 2, offset+4);
		char * objYPos = pgsUtil::subArray(buffer, 2, offset+6);
		offset += 8;
		if(pgsUtil::cleanChar(objCropFlag[0]) == 0x40)
		{
			char * objCropXPos = pgsUtil::subArray(buffer, 2, offset);
			char * objCropYPos = pgsUtil::subArray(buffer, 2, offset+2);
			char * objCropWidth = pgsUtil::subArray(buffer, 2, offset+4);
			char * objCropHeight = pgsUtil::subArray(buffer, 2, offset+6);
			offset += 8;
			compObjects[i] = compositionObject(objID, windowID, objCropFlag, objXPos, objYPos, objCropXPos, objCropYPos, objCropWidth, objCropHeight);
		}
		else { compObjects[i] = compositionObject(objID, windowID, objCropFlag, objXPos, objYPos); }
	}
	return presentationCompositionSegment(width, height, framerate, compNumber, compState, paletteUpdateFlag, paletteID, compObjectCount, compObjects);
}

windowDefinitionSegment pgsParser::parseWDS(char * buffer, unsigned int segmentSize)
{
	char * numOfWindows = pgsUtil::subArray(buffer, 1);
	unsigned int count = pgsUtil::cleanChar(numOfWindows[0]);
	windowSegment * windowSegments = new windowSegment[count];
	for(int i = 0; i < count; i++)
	{
		char * windowID = pgsUtil::subArray(buffer, 1, 1+i*9);
		char * windowXPos = pgsUtil::subArray(buffer, 2, 1+i*9);
		char * windowYPos = pgsUtil::subArray(buffer, 2, 1+i*9);
		char * windowWidth = pgsUtil::subArray(buffer, 2, 1+i*9);
		char * windowHeight = pgsUtil::subArray(buffer, 2, 1+i*9);
		windowSegments[i] = windowSegment(windowID, windowXPos, windowYPos, windowWidth, windowHeight);
	}
	return windowDefinitionSegment(numOfWindows, windowSegments);
}

paletteDefinitionSegment pgsParser::parsePDS(char * buffer, unsigned int segmentSize)
{
	unsigned int segmentCount = (segmentSize - 2) / 5;
	char * paletteID = pgsUtil::subArray(buffer, 1);
	char * paletteVersionNumber = pgsUtil::subArray(buffer, 1, 1);
	paletteSegment * paletteSegments = new paletteSegment[segmentCount];
	for(int i = 0; i < segmentCount; i++)
	{
		char * paletteEntryID = pgsUtil::subArray(buffer, 1, 2+5*i);
		char * luminance = pgsUtil::subArray(buffer, 1, 3+5*i);
		char * colorDiffRed = pgsUtil::subArray(buffer, 1, 4+5*i);
		char * colorDiffBlue = pgsUtil::subArray(buffer, 1, 5+5*i);
		char * transparency = pgsUtil::subArray(buffer, 1, 6+5*i);
		paletteSegments[i] = paletteSegment(paletteEntryID, luminance, colorDiffRed, colorDiffBlue, transparency);
	}
	return paletteDefinitionSegment(paletteID, paletteVersionNumber, paletteSegments, segmentCount);
}

objectDefinitionSegment pgsParser::parseODS(char * buffer, unsigned long segmentSize)
{
	char * objectID = pgsUtil::subArray(buffer, 2);
	char * objectVersionNumber = pgsUtil::subArray(buffer, 1, 2);
	char * lastInSequenceFlag = pgsUtil::subArray(buffer, 1, 3);
	char * objectDataLength = pgsUtil::subArray(buffer, 3, 4);
	char * width = pgsUtil::subArray(buffer, 2, 7);
	char * height = pgsUtil::subArray(buffer, 2, 9);
	char * data = pgsUtil::subArray(buffer, 11, pgsUtil::char3ToLong(objectDataLength));
	return objectDefinitionSegment(objectID, objectVersionNumber, lastInSequenceFlag, objectDataLength, width, height, data);
}


std::map<int, pgsSegment> pgsParser::parseAllSegments()
{
	int count = 0;
	while (!this->pgsData.eof())
	{
		this->PGS_SEGMENTS[count] = this->parseNextSegment();
		if(PGS_SEGMENTS[count].HEADER.SEGMENT_TYPE == END) { break; }
		this->pgsData.peek();
		count++;
	}
	return this->PGS_SEGMENTS;
};
