#include <fstream>
#include <bits/stdc++.h>
#include <tesseract/baseapi.h>
#include <libavcodec/avcodec.h>
#include <string>
#include <stdlib.h>
#include "pgsParser.h"
#include "pgsSegment.h"

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
