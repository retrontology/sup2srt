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
#include "pgsSegmentHeader.h"
#include "presentationCompositionSegment.h"
#include "windowDefinitionSegment.h"
#include "paletteDefinitionSegment.h"
#include "objectDefinitionSegment.h"
#include "objectData.h"

class pgsParser
{
	private:
		std::ifstream pgsData;
		std::map<int, pgsSegment>  PGS_SEGMENTS;
	public:
        pgsParser();
		pgsParser(std::string filename);
		virtual ~pgsParser();
		void open(std::string filename);
		pgsSegmentHeader parseHeader(char * buffer);
		std::map<int, pgsSegment> parseAllSegments();
		pgsSegment parseNextSegment();
		presentationCompositionSegment parsePCS(char * buffer, unsigned int segmentSize);
		windowDefinitionSegment parseWDS(char * buffer, unsigned int segmentSize);
		paletteDefinitionSegment parsePDS(char * buffer, unsigned int segmentSize);
		objectDefinitionSegment parseODS(char * buffer, unsigned long segmentSize);
};

#endif /* PGSPARSER_H_ */
