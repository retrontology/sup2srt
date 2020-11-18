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
#include "mkvUtil.h"

std::string usage = "usage: sup2srt [-h] [-vST] [-t track] -l language [-o output] input\n\n\t-h:\n\t\tDisplay this help menu\n\n\t-v:\n\t\tVerbose - output srt as it's being written\n\n\t-T:\n\t\tDump TIFF images extracted from the PGS file to disk\n\n\t-S:\n\t\tWrite SUP file extracted from mkv to disk (only used when an mkv is input)\n\n\t-t track:\n\t\tSelect track to extract from mkv (must be used when an mkv is input)\n\n\t-l language:\n\t\tSelect Tesseract language according to ISO-3166\n\n\t-o:\n\t\tOutput file (if not specified the file will be output to the same dir as the input).\n\n\tinput:\n\t\tfile to parse SUP stream. Can either be a binary SUP file or an mkv. If the file doesn't end in .mkv, it will assume it is a binary SUP file.\n\n";
std::string input;
std::string output = std::string("-1");
std::string language = std::string("-1");
int track = -1;
bool verbose = false;
bool dumpTIFF = false;
bool dumpSUP = false;
bool mkv = false;


void parseArgs(int argc, char** argv)
{
	extern char *optarg;
	extern int optind;
	int o;
	while ((o = getopt (argc, argv, "hTSl:ot:v")) != -1)
	{
		switch(o)
		{

			case 'h':
			{
				std::cout << usage;
				exit(0);
			}
			case 'T':
			{
				dumpTIFF = true;
				break;
			}
			case 'S':
			{
				dumpSUP = true;
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
			case 't':
			{
				track = atoi(optarg);
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
		input = std::string(argv[optind]);
		if(input.find('.') < input.length())
		{
			mkv = input.substr(input.find_last_of('.') + 1).compare("mkv") == 0;
		}
	}
	if(mkv && track == -1)
	{
		std::cerr << "Please supply a track index if you input an mkv file" << std::endl;
		std::cerr << usage;
		exit(1);
	}
	if(language.compare("-1") == 0)
	{
		std::cerr << "Please supply a language according to ISO-3166" << std::endl;
		std::cerr << usage;
		exit(1);
	}
	if(output.compare("-1") == 0)
	{
		if(input.find(".") < input.length() && (input.substr(input.find_last_of('.') + 1).compare("sup") == 0 || mkv))
		{
			output = input.substr(0, input.find_last_of('.'));
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
	std::stringstream pgs;
	if(mkv)
	{
		std::cout << "Extracting SUP stream from mkv..." << std::endl;
		pgs << mkvUtil::extractMKVsup(input, track).str();
		std::cout << "Stream is extracted" << std::endl;
		if(dumpSUP)
		{
			std::ofstream file;
			std::string supFile = input.substr(0, input.find_last_of('.')) + "." + std::to_string(track) + ".sup";
			file.open(supFile, std::ifstream::binary);
			file << pgs.str();
			file.close();
			std::cout << "SUP file written to: " + supFile << std::endl;
		}
	}
	else
	{
		std::cout << "Reading SUP from file..." << std::endl;
		std::ifstream file;
		file.open(input, std::ifstream::binary);
		pgs << file.rdbuf();
		file.close();
		std::cout << "SUP file has been read" << std::endl;
	}
	pgsParser pgsp(&pgs);
	if(dumpTIFF)
	{
		std::string path = output + ".TIFFs";;
		std::cout << "TIFF files being written to: " + path << std::endl;
		pgsp.dumpTIFFs(path, true);
		std::cout << "TIFF files have been written" << std::endl;
	}
	std::cout << "Starting OCR on extracted images..." << std::endl;
	srtUtil::pgsToSRTFile(&pgsp, output.c_str(), language.c_str(), verbose);
	std::cout << "OCR finished and SRT written to: " + output << std::endl;
    return 0;
}
