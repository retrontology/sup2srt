/*
 * sup2srt.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "pgsUtil.h"
#include "pgsParser.h"


int main(int argc, char** argv)
{
	std::string filename = argv[1];
	pgsParser pgsp(filename);
	//pgsUtil::dumpBMPs(pgsp.PGS_SEGMENTS);
	//std::cout << filename << std::endl;
    return 0;
}
