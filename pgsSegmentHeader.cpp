/*
 * pgsSegmentHeader.cpp
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#include "pgsSegmentHeader.h"
#include <string>

pgsSegmentHeader::pgsSegmentHeader(){};

pgsSegmentHeader::pgsSegmentHeader(char * pgs, char * dts, char * st, char * ss) {
	this->PRESENTATION_TIMESTAMP = std::string(pgs, 4);
	this->DECODING_TIMESTAMP = std::string(dts, 4);
	this->SEGMENT_TYPE = std::string(st, 1);
	this->SEGMENT_SIZE = std::string(ss, 2);
};

pgsSegmentHeader::~pgsSegmentHeader() {
	// TODO Auto-generated destructor stub
};

std::string pgsSegmentHeader::getPTS() { return this->PRESENTATION_TIMESTAMP; }

std::string pgsSegmentHeader::getDTS() { return this->DECODING_TIMESTAMP; }

std::string pgsSegmentHeader::getType() { return this->SEGMENT_TYPE; }

std::string pgsSegmentHeader::getSize() { return this->SEGMENT_SIZE; }

