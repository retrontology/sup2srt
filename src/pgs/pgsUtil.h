/*
 * pgsUtil.h
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#ifndef PGSUTIL_H_
#define PGSUTIL_H_

#include "pgsSegment.h"
#include <bits/stdc++.h>
#include "objectDefinitionSegment.h"
#include "paletteDefinitionSegment.h"

namespace pgsUtil
{
	unsigned long int char4ToLong(char * ptr);
	unsigned long int char3ToLong(char * ptr);
	unsigned int char2ToInt(char * ptr);
	unsigned char cleanChar(char in);
	double ptsToMilli(unsigned long in);
	void decodeRLE(unsigned long ** pixels, paletteDefinitionSegment pds, objectDefinitionSegment ods);
	void decodeRLEtoBMP(unsigned long * out, paletteDefinitionSegment pds, objectDefinitionSegment ods);
	void numToChars(char * out, unsigned long long num, unsigned int length);
}


#endif /* PGSUTIL_H_ */
