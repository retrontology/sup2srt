/*
 * pgsSegmentHeader.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsSegmentHeader.h"
#include "pgsUtil.h"

pgsSegmentHeader::pgsSegmentHeader()
{
	this->PRESENTATION_TIMESTAMP = 0;
	this->DECODING_TIMESTAMP = 0;
	this->SEGMENT_TYPE = ERR;
	this->SEGMENT_SIZE = 0;
};

pgsSegmentHeader::pgsSegmentHeader(char * pts, char * dts, char * st, char * ss)
{
	this->PRESENTATION_TIMESTAMP = pgsUtil::char4ToLong(pts);
	this->DECODING_TIMESTAMP = pgsUtil::char4ToLong(dts);
	this->SEGMENT_TYPE = static_cast<pgsSegmentType>(pgsUtil::cleanChar(st[0]));
	this->SEGMENT_SIZE = pgsUtil::char2ToInt(ss);
};

pgsSegmentHeader::~pgsSegmentHeader()
{
	// TODO Auto-generated destructor stub
};

