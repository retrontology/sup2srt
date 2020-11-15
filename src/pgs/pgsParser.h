/*
 * pgsParser.h
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */

#ifndef PGSPARSER_H_
#define PGSPARSER_H_

#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include "pgsSegment.h"
#include "pgsSegmentHeader.h"
#include "presentationCompositionSegment.h"
#include "windowDefinitionSegment.h"
#include "paletteDefinitionSegment.h"
#include "objectDefinitionSegment.h"
#include "displaySegment.h"

class pgsParser
{
	private:
		std::stringstream pgsData;
	public:
		std::vector<std::unique_ptr<pgsSegment>>  PGS_SEGMENTS;
		std::vector<displaySegment> displaySegments;
        pgsParser();
		pgsParser(std::stringstream * pgs);
		virtual ~pgsParser();
		pgsSegmentHeader parseHeader(char * buffer);
		void parseDisplaySegments();
		void parseAllSegments();
		std::unique_ptr<pgsSegment> parseNextSegment();
		presentationCompositionSegment parsePCS(char * buffer, unsigned int segmentSize);
		windowDefinitionSegment parseWDS(char * buffer, unsigned int segmentSize);
		paletteDefinitionSegment parsePDS(char * buffer, unsigned int segmentSize);
		objectDefinitionSegment parseODS(char * buffer, unsigned long segmentSize);
		void dumpTIFFs(std::string path);
		void dumpRLEs();
		void printDisplaySegments();
};

#endif /* PGSPARSER_H_ */
