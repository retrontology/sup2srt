/*
 * pgsSegmentHeader.h
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#ifndef PGSSEGMENTHEADER_H_
#define PGSSEGMENTHEADER_H_

#include <string>

enum pgsSegmentType
{
	PDS = 0x14,
	ODS = 0x15,
	PCS = 0x16,
	WDS = 0x17,
	END = 0x80,
	ERR = 0x00
};

class pgsSegmentHeader {
public:
	pgsSegmentHeader();
	pgsSegmentHeader(char * pgs, char * dts, char * st, char * ss);
	virtual ~pgsSegmentHeader();
	unsigned long int PRESENTATION_TIMESTAMP;
	unsigned long int DECODING_TIMESTAMP;
	pgsSegmentType SEGMENT_TYPE;
	unsigned int SEGMENT_SIZE;
};

#endif /* PGSSEGMENTHEADER_H_ */
