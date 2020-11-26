#include "mkvUtil.h"
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <vector>

std::string usage = "";
std::string input;
std::vector<unsigned int> tracks;

void parseArgs(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int o;
	while ((o = getopt (argc, argv, "ht:")) != -1)
	{
		switch(o)
		{

			case 'h':
			{
				std::cout << usage;
				exit(0);
			}
			case 't':
			{
				std::string trackString(optarg);
				tracks = mkvUtil::parseTracks(trackString);
				break;
			}
			case '?':
			{
				std::cerr << "Did not understand argument: " << o <<std::endl;
				std::cerr << usage;
				exit(1);
			}
		}
	}
	if ((optind+1) != argc)
	{
		std::cerr << "Please supply an mkv file" << std::endl;
		std::cerr << usage;
		exit(1);
	}
	else
	{
		input = std::string(argv[optind]);
		if(!(input.find('.') < input.length() && input.substr(input.find_last_of('.') + 1).compare("mkv") == 0))
		{
			std::cerr << "Please supply an mkv file" << std::endl;
			std::cerr << usage;
			exit(1);
		}
	}
}

int main(int argc, char** argv)
{
	parseArgs(argc, argv);
	if(tracks.size() == 0) mkvUtil::dumpAllMKVsup(input);
	else mkvUtil::dumpSelectMKVsup(input, tracks);
}
