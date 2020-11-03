/*
 * pgsSegmentHeader.h
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#ifndef PGSSEGMENTHEADER_H_
#define PGSSEGMENTHEADER_H_

#include <string>

class pgsSegmentHeader {
private:
	std::string PRESENTATION_TIMESTAMP;
	std::string DECODING_TIMESTAMP;
	std::string SEGMENT_TYPE;
	std::string SEGMENT_SIZE;
public:
	pgsSegmentHeader();
	pgsSegmentHeader(char * pgs, char * dts, char * st, char * ss);
	virtual ~pgsSegmentHeader();
	std::string getPTS();
	std::string getDTS();
	std::string getType();
	std::string getSize();
};

#endif /* PGSSEGMENTHEADER_H_ */
