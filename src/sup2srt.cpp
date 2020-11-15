/*
 * sup2srt.cpp
 *
 *  Created on: Nov 1, 2020
 *      Author: blazer
 */
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "pgs/pgsParser.h"
#include "pgs/pgsUtil.h"
#include "srtUtil.h"

std::string usage = "usage: sup2srt [-h] [-vd] [-t track] -l language [-o output] input\n";
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
	while ((o = getopt (argc, argv, "hdl:ot:v")) != -1)
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
		if(input.find(".") < input.length())
		{
			if(input.substr(input.find_last_of('.') + 1).compare("sup") == 0 || mkv)
			{
				output = input.substr(0, input.find_last_of('.'));
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

void tsToChar4(char * buffer, u_int32_t ts)
{
	buffer[0] = (ts & 0xFF000000) >> 24;
	buffer[1] = (ts & 0x00FF0000) >> 16;
	buffer[2] = (ts & 0x0000FF00) >> 8;
	buffer[3] = ts & 0x000000FF;
}

std::ostringstream extractMKVTrack(std::string filename, int index)
{
	std::ostringstream out;
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	AVPacket * packet = av_packet_alloc();
	while (av_read_frame(mkvFile, packet) >= 0)
	{
		if (packet->stream_index == index)
		{
			int offset = 0;
			while(offset < packet->size)
			{
				unsigned int segSize = pgsUtil::char2ToInt(reinterpret_cast<char *>(packet->data + offset + 1));
				out << "PG";
				char * buffer = new char[4];
				u_int32_t pts = packet->pts * 90;
				u_int32_t dts = packet->dts * 90;
				tsToChar4(buffer, pts);
				out << std::string(buffer, 4);
				tsToChar4(buffer, dts);
				out << std::string(buffer, 4);
				out << std::string(reinterpret_cast<char *>(packet->data + offset), segSize + 3);
				offset += 3 + segSize;
			}

		}
	}
	return out;
}

int main(int argc, char** argv)
{
	parseArgs(argc, argv);
	if(mkv)
	{
		std::ofstream file;
		file.open("test.sup", std::ifstream::binary);
		file << extractMKVTrack(input, track).str();
		file.close();
	}
	else
	{
		pgsParser pgsp(input);
		if(dump) pgsp.dumpTIFFs();
		srtUtil::pgsToSRTFile(&pgsp, output.c_str(), language.c_str(), verbose);
	}

    return 0;
}
