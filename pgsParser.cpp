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
#include "pgsParser.h"
#include "pgsSegment.h"
#include "pgsSegmentHeader.h"

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
};

pgsSegment pgsParser::parseNextSegment()
{
	char * buffer = new char [2];
	this->pgsData.read(buffer, 2);
	std::string magicNumber (buffer);
	if (magicNumber == "PG")
	{
		std::cout << "MAGIC NUMBER FOUND!" << std::endl;
		// Read Header
		char * pts = new char [4];
		this->pgsData.read(pts, 4);
		char * dts = new char [4];
		this->pgsData.read(dts, 4);
		char * type = new char [1];
		this->pgsData.read(type, 1);
		char * size = new char [2];
		this->pgsData.read(size, 2);
		pgsSegmentHeader header = pgsSegmentHeader(pts, dts, type, size);
		pgsSegment segment = pgsSegment(header);
	}
	else
	{
		std::cout << "Failed to find magic number. Either stream is corrupt or you dun fukt up son :|" << std::endl;
		exit (EXIT_FAILURE);
	}
};

pgsSegment * pgsParser::parseAllSegments()
{
	while (!this->pgsData.eof())
	{
		this->parseNextSegment();
		this->pgsData.peek();
	}
};
