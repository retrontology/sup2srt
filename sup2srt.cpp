#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "pgsParser.h"


int main(int argc, char** argv)
{
	std::string filename = argv[1];
	pgsParser pgsp(filename);
	//std::cout << filename << std::endl;
    return 0;
}
