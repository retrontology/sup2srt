/*
 * sup2srt.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */
#include <iostream>
#include <string>
#include "pgs/pgsParser.h"
#include "srtUtil.h"


int main(int argc, char** argv)
{
	std::string filename = argv[1];
	pgsParser pgsp(filename);
	//pgsp.printDisplaySegments();
	//pgsp.dumpRLEs();
	//pgsp.dumpBMPs();
	//pgsp.dumpTIFFs();
	//srtUtil::dumpTIFFStrings(&pgsp, "eng");
	srtUtil::pgsToSRT(&pgsp, "eng");
    return 0;
}
