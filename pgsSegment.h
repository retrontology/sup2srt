/*
 * pgsSegment.h
 *
 *  Created on: Nov 2, 2020
 *      Author: blazer
 */

#ifndef PGSSEGMENT_H_
#define PGSSEGMENT_H_

class pgsSegment {
private:
	char * PRESENTATION_TIMESTAMP = new char [4];
	char * DECODING_TIMESTAMP = new char [4];
	char * SEGMENT_TYPE = new char;
	char * SEGMENT_SIZE = new char [2];
public:
	pgsSegment(char * pgs, char * dts, char * st, char * ss, char * data);
	virtual ~pgsSegment();
};

#endif /* PGSSEGMENT_H_ */
