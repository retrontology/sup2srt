/*
 * pgsSegment.cpp
 *
 *  Created on: Nov 2, 2020
 *      Author: blazer
 */

#include "pgsSegment.h"

pgsSegment::pgsSegment(char * pgs, char * dts, char * st, char * ss, char * data) {
	this->PRESENTATION_TIMESTAMP = pgs;

}

pgsSegment::~pgsSegment() {
	// TODO Auto-generated destructor stub
}

