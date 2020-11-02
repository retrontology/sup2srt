/*
 * pgsParser.h
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */

#ifndef PGSPARSER_H_
#define PGSPARSER_H_

#include <string>
#include <fstream>
#include "pgsSegment.h"

class pgsParser
{
	private:
		std::ifstream pgsData;
        pgsSegment * PGS_SEGMENTS;
	public:
        pgsParser();
		pgsParser(std::string filename);
		virtual ~pgsParser();
		void open(std::string filename);
		pgsSegment * parseAllSegments();
		pgsSegment parseNextSegment();
};

#endif /* PGSPARSER_H_ */
