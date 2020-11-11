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
	void decodeRLE(char * out, paletteDefinitionSegment pds, objectDefinitionSegment ods);
}


#endif /* PGSUTIL_H_ */
