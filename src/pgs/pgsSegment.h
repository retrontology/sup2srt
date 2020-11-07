/*
 * pgsSegment.h
 *
 *  Created on: Nov 2, 2020
 *      Author: blazer
 */

#ifndef PGSSEGMENT_H_
#define PGSSEGMENT_H_
#include "pgsSegmentHeader.h"

class pgsSegment {
private:
public:
	pgsSegmentHeader HEADER;
	pgsSegment(pgsSegmentHeader header);
	pgsSegment();
	virtual ~pgsSegment();
};

#endif /* PGSSEGMENT_H_ */
