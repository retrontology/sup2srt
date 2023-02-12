#include "mkvUtil.h"
#include "sup2srtConfig.h"
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <vector>

std::string usage = "usage: sup2disk [-hv] [-t track] input\n\n  -h:        Display this help menu\n  -v:        Display program Version\n  -t track:  Select track to extract from mkv. Can be multiple tracks separated by a comma (must be used when an mkv is input)\n  input:     file to parse SUP stream. Must be an mkv\n";
std::string version = std::to_string(sup2srt_VERSION_MAJOR) + "." + std::to_string(sup2srt_VERSION_MINOR) + "." + std::to_string(sup2srt_VERSION_PATCH);
std::string input;
std::vector<unsigned int> tracks;

void parseArgs(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int o;
	while ((o = getopt (argc, argv, "ht:v")) != -1)
	{
		switch(o)
		{

			case 'h':
			{
				std::cout << usage << std::endl;
				exit(0);
			}
			case 't':
			{
				std::string trackString(optarg);
				tracks = mkvUtil::parseTracks(trackString);
				break;
			}
			case 'v':
			{
				std::cout << "sup2disk version " << version << std::endl;
				exit(0);
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
