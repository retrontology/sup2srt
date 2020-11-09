/*
 * displaySegment.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#include "displaySegment.h"

displaySegment::displaySegment()
{

}

displaySegment::displaySegment(presentationCompositionSegment pcs)
{
	this->pcs = pcs;
}

displaySegment::displaySegment(presentationCompositionSegment pcs, std::vector<windowDefinitionSegment> wds, std::vector<paletteDefinitionSegment> pds, std::vector<objectDefinitionSegment> ods, pgsSegment end) {
	this->pcs = pcs;
	this->wds = wds;
	this->pds = pds;
	this->ods = ods;
	this->end = end;
}

displaySegment::~displaySegment() {
	// TODO Auto-generated destructor stub
}

