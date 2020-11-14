/*
 * sup2srt.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "pgs/pgsParser.h"
#include "srtUtil.h"

std::string usage = "usage: sup2srt [-h] [-vd] -l language [-o output] input\n";
std::string input;
std::string output = std::string("-1");
std::string language = std::string("-1");
int track = -1;
bool verbose = false;
bool dump = false;
bool mkv = false;


void parseArgs(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int o;
	while ((o = getopt (argc, argv, "hdl:o:v")) != -1)
	{
		switch(o)
		{

			case 'h':
			{
				std::cout << usage;
				exit(0);
			}
			case 'd':
			{
				dump = true;
				break;
			}
			case 'l':
			{
				language = std::string(optarg);
				break;
			}
			case 'o':
			{
				output = std::string(optarg);
				break;
			}
			case 'v':
			{
				verbose = true;
				break;
			}
			case '?':
			{
				std::cerr << usage;
				exit(1);
			}
		}
	}
	if ((optind+1) != argc)
	{
		std::cerr << "Please supply an input file" << std::endl;
		std::cerr << usage;
		exit(1);
	}
	else
	{
		if(input.find(".") < input.length())
		{
			mkv = input.substr(input.find_last_of(".") + 1).compare("mkv") == 0;
		}
		input = std::string(argv[optind]);
	}
	if(language.compare("-1") == 0)
	{
		std::cerr << "Please supply a language according to ISO-3166" << std::endl;
		std::cerr << usage;
		exit(1);
	}
	if(output.compare("-1") == 0)
	{
		if(input.find(".") < input.length())
		{
			if(input.substr(input.find_last_of(".") + 1).compare("sup") == 0 || mkv)
			{
				output = input.substr(0, input.find_last_of("."));
			}
			else
			{
				output = input;
			}
		}
		else
		{
			output = input;
		}
		output += "." + language + ".srt";
	}
}

int main(int argc, char** argv)
{
	parseArgs(argc, argv);
	pgsParser pgsp(input);
	if(dump) pgsp.dumpTIFFs();
	srtUtil::pgsToSRTFile(&pgsp, output.c_str(), language.c_str(), verbose);
    return 0;
}
