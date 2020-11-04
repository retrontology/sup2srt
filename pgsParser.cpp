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
	this->parseNextSegment();
};

pgsSegment pgsParser::parseNextSegment()
{
	char * buffer = new char [13];
	this->pgsData.read(buffer, 13);
	pgsSegmentHeader header = this->parseHeader(buffer);
	// Segment Type
	switch (header.SEGMENT_TYPE)
	{
		case PDS :
		{
			//statements;
			break;
		}
		case ODS :
		{
			//statements;
			break;
		}
		case PCS :
		{
			char * buffer = new char [11];
			this->pgsData.read(buffer, 11);
			presentationCompositionSegment pcs = this->parsePCS(buffer);
			break;
		}
		case WDS :
		{
			//statements;
			break;
		}
		case END :
		{
			//statements;
			break;
		}
		case ERR :
		{
			std::cout << "Failed to find magic number. Either stream is corrupt or you dun fukt up son :|" << std::endl;
			exit (EXIT_FAILURE);
			break;
		}
	}
	pgsSegment segment = pgsSegment(header);
	return segment;

};

pgsSegmentHeader pgsParser::parseHeader(char * head)
{
	// Check for magic number
	std::string magicNumber (pgsUtil::subArray(head, 2));
	if (magicNumber == "PG")
	{
		// Read Header
		char * pts = pgsUtil::subArray(head, 4, 2);
		char * dts = pgsUtil::subArray(head, 4, 6);
		char * type = pgsUtil::subArray(head, 1, 10);
		char * size = pgsUtil::subArray(head, 2, 11);
		return pgsSegmentHeader(pts, dts, type, size);
	}
	else
	{
		return pgsSegmentHeader();
	}

}

presentationCompositionSegment pgsParser::parsePCS(char * buffer)
{

}

pgsSegment * pgsParser::parseAllSegments()
{
	while (!this->pgsData.eof())
	{
		this->parseNextSegment();
		this->pgsData.peek();
	}
};
