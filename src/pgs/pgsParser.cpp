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
#include <vector>
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
#include "displaySegment.h"
#include "../bmp/bitmap.h"

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
	this->parseDisplaySegments();
	this->pgsData.close();
};

std::unique_ptr<pgsSegment> pgsParser::parseNextSegment()
{
	char * buffer = new char [13];
	this->pgsData.read(buffer, 13);
	pgsSegmentHeader header = this->parseHeader(buffer);
	std::unique_ptr<pgsSegment> segment;
	buffer = new char[header.SEGMENT_SIZE];
	if(header.SEGMENT_SIZE > 0) { this->pgsData.read(buffer, header.SEGMENT_SIZE); }
	switch (header.SEGMENT_TYPE)
	{
		case PDS :
		{
			segment = std::make_unique<paletteDefinitionSegment>(this->parsePDS(buffer, header.SEGMENT_SIZE));
			break;
		}
		case ODS :
		{
			segment = std::make_unique<objectDefinitionSegment>(this->parseODS(buffer, header.SEGMENT_SIZE));
			break;
		}
		case PCS :
		{
			segment = std::make_unique<presentationCompositionSegment>(this->parsePCS(buffer, header.SEGMENT_SIZE));
			break;
		}
		case WDS :
		{
			segment = std::make_unique<windowDefinitionSegment>(this->parseWDS(buffer, header.SEGMENT_SIZE));
			break;
		}
		case END :
		{
			segment = std::make_unique<pgsSegment>(pgsSegment());
			break;
		}
		case ERR :
		{
			std::cout << "Failed to find magic number. Either stream is corrupt or you dun fukt up son :|" << std::endl;
			exit (EXIT_FAILURE);
			break;
		}
	}
	segment->HEADER = header;
	return segment;
};

pgsSegmentHeader pgsParser::parseHeader(char * buffer)
{
	// Check for magic number
	pgsSegmentHeader header;
	std::string magicNumber (buffer, 2);
	if (magicNumber == "PG")
	{
		// Read Header
		char * pts = buffer + 2;
		char * dts = buffer + 6;
		char * type = buffer + 10;
		char * size = buffer + 11;
		header =pgsSegmentHeader(pts, dts, type, size);
	}
	return header;
}

presentationCompositionSegment pgsParser::parsePCS(char * buffer, unsigned int segmentSize)
{
	char * width = buffer;
	char * height = buffer + 2;
	char * framerate = buffer + 4;
	char * compNumber = buffer + 5;
	char * compState = buffer + 7;
	char * paletteUpdateFlag = buffer + 8;
	char * paletteID = buffer + 9;
	char * compObjectCount = buffer + 10;
	unsigned int count = pgsUtil::cleanChar(compObjectCount[0]);
	std::vector<compositionObject> compObjects;
	unsigned int offset = 11;
	// Parse Objects
	for(int i = 0; i < count; i++)
	{
		// Read only first 4 so we know how big the object is before reading the rest
		char * objID = buffer + offset;
		char * windowID = buffer + offset+2;
		char * objCropFlag = buffer + offset+3;
		char * objXPos = buffer + offset+4;
		char * objYPos = buffer + offset+6;
		offset += 8;
		if(pgsUtil::cleanChar(objCropFlag[0]) == 0x40)
		{
			char * objCropXPos = buffer + offset;
			char * objCropYPos = buffer + offset+2;
			char * objCropWidth = buffer + offset+4;
			char * objCropHeight = buffer + offset+6;
			offset += 8;
			compObjects.push_back(compositionObject(objID, windowID, objCropFlag, objXPos, objYPos, objCropXPos, objCropYPos, objCropWidth, objCropHeight));
		}
		else { compObjects.push_back(compositionObject(objID, windowID, objCropFlag, objXPos, objYPos)); }
	}
	return presentationCompositionSegment(width, height, framerate, compNumber, compState, paletteUpdateFlag, paletteID, compObjectCount, compObjects);
}

windowDefinitionSegment pgsParser::parseWDS(char * buffer, unsigned int segmentSize)
{
	char * numOfWindows = buffer;
	unsigned int count = pgsUtil::cleanChar(numOfWindows[0]);
	std::vector<windowSegment> windowSegments;
	for(int i = 0; i < count; i++)
	{
		char * windowID = buffer + 1+i*9;
		char * windowXPos = buffer + 2+i*9;
		char * windowYPos = buffer + 4+i*9;
		char * windowWidth = buffer + 6+i*9;
		char * windowHeight = buffer + 8+i*9;
		windowSegments.push_back(windowSegment(windowID, windowXPos, windowYPos, windowWidth, windowHeight));
	}
	return windowDefinitionSegment(numOfWindows, windowSegments);
}

paletteDefinitionSegment pgsParser::parsePDS(char * buffer, unsigned int segmentSize)
{
	unsigned int segmentCount = (segmentSize - 2) / 5;
	char * paletteID = buffer;
	char * paletteVersionNumber = buffer+1;
	std::vector<paletteSegment> paletteSegments;
	for(int i = 0; i < segmentCount; i++)
	{
		char * paletteEntryID = buffer+2+5*i;
		char * luminance = buffer+3+5*i;
		char * colorDiffRed = buffer+4+5*i;
		char * colorDiffBlue = buffer+5+5*i;
		char * transparency = buffer+6+5*i;
		paletteSegments.push_back(paletteSegment(paletteEntryID, luminance, colorDiffRed, colorDiffBlue, transparency));
	}
	return paletteDefinitionSegment(paletteID, paletteVersionNumber, paletteSegments, segmentCount);
}

objectDefinitionSegment pgsParser::parseODS(char * buffer, unsigned long segmentSize)
{
	char * objectID = buffer;
	char * objectVersionNumber = buffer + 2;
	char * lastInSequenceFlag = buffer + 3;
	char * objectDataLength = buffer + 4;
	char * width = buffer + 7;
	char * height = buffer + 9;
	char * data = buffer + 11;
	return objectDefinitionSegment(objectID, objectVersionNumber, lastInSequenceFlag, objectDataLength, width, height, data);
}


void pgsParser::parseAllSegments()
{
	while (!this->pgsData.eof())
	{
		this->PGS_SEGMENTS.push_back(std::move(this->parseNextSegment()));
		this->pgsData.peek();
	}
};

void pgsParser::parseDisplaySegments()
{
	if(this->PGS_SEGMENTS.size() == 0){ this->parseAllSegments(); }
	this->displaySegments.clear();
	displaySegment ds;
	std::vector<windowDefinitionSegment> wds;
	std::vector<paletteDefinitionSegment> pds;
	std::vector<objectDefinitionSegment> ods;
	for(int i = 0; i < this->PGS_SEGMENTS.size(); i++)
	{
		switch(this->PGS_SEGMENTS[i]->HEADER.SEGMENT_TYPE)
		{
			case PCS :
			{
				presentationCompositionSegment* pcs = dynamic_cast<presentationCompositionSegment*>(this->PGS_SEGMENTS[i].get());
				ds = displaySegment(*pcs);
				wds.clear();
				pds.clear();
				ods.clear();
				break;
			}
			case WDS :
			{
				windowDefinitionSegment* temp = dynamic_cast<windowDefinitionSegment*>(this->PGS_SEGMENTS[i].get());
				wds.push_back(*temp);
				break;
			}
			case PDS :
			{
				paletteDefinitionSegment* temp = dynamic_cast<paletteDefinitionSegment*>(this->PGS_SEGMENTS[i].get());
				pds.push_back(*temp);
				break;
			}
			case ODS :
			{
				objectDefinitionSegment* temp = dynamic_cast<objectDefinitionSegment*>(this->PGS_SEGMENTS[i].get());
				ods.push_back(*temp);
				break;
			}
			case END :
			{
				ds.wds = wds;
				ds.pds = pds;
				ds.ods = ods;
				ds.end = *this->PGS_SEGMENTS[i].get();
				this->displaySegments.push_back(ds);
				break;
			}
		}
	}
}

void pgsParser::dumpBMPs()
{
	system("mkdir -p img");
	int count = 0;
	for(int i = 0; i < this->displaySegments.size(); i++)
	{
		if(this->displaySegments[i].ods.size()==1)
		{
			std::ostringstream ss;
			ss << std::setw(5) << std::setfill('0') << std::to_string(count);
			std::ofstream file;
			file.open("img/" + ss.str() + ".bmp", std::ifstream::binary);
			bitmap bmp = this->displaySegments[i].getBitmap();
			char * data = new char[bmp.fileHeader.fileSize];
			bmp.getByteArray(data);
			file.write(data, bmp.fileHeader.fileSize);
			file.close();
			count++;
		}
	}
};

void pgsParser::dumpRLEs()
{
	system("mkdir -p img");
	int count = 0;
	for(int i = 0; i < this->displaySegments.size(); i++)
	{
		if(this->displaySegments[i].ods.size()==1)
		{
			std::ostringstream ss;
			ss << std::setw(5) << std::setfill('0') << std::to_string(count);
			std::ofstream file;
			file.open("img/" + ss.str() + ".rle", std::ifstream::binary);
			char * out = this->displaySegments[i].ods[0].data;
			file.write(out, this->displaySegments[i].ods[0].objectDataLength);
			file.close();
			count++;
		}
	}
}
