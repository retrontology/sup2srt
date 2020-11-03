/*
 * pgsSegment.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: blazer
 */

#include "pgsSegment.h"

pgsSegment::pgsSegment(pgsSegmentHeader header) {
	this->HEADER = header;
};

pgsSegment::~pgsSegment() {
	// TODO Auto-generated destructor stub
};

