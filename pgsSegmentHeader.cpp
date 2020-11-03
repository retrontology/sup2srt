/*
 * pgsSegmentHeader.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsSegmentHeader.h"
#include "pgsUtil.h"

pgsSegmentHeader::pgsSegmentHeader(){};

pgsSegmentHeader::pgsSegmentHeader(char * pts, char * dts, char * st, char * ss) {

	this->PRESENTATION_TIMESTAMP = char4ToLong(pts);
	this->DECODING_TIMESTAMP = char4ToLong(dts);
	this->SEGMENT_TYPE = static_cast<pgsSegmentType>(st[0]);
	this->SEGMENT_SIZE = char2ToLong(ss);
};

pgsSegmentHeader::~pgsSegmentHeader() {
	// TODO Auto-generated destructor stub
};

unsigned long int pgsSegmentHeader::getPTS() { return this->PRESENTATION_TIMESTAMP; }

unsigned long int pgsSegmentHeader::getDTS() { return this->DECODING_TIMESTAMP; }

pgsSegmentType pgsSegmentHeader::getType() { return this->SEGMENT_TYPE; }

unsigned int pgsSegmentHeader::getSize() { return this->SEGMENT_SIZE; }

