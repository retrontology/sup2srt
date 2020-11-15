/*
 * mkvUtil.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: blazer
 */

#include "mkvUtil.h"
#include "pgs/pgsUtil.h"
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}


void mkvUtil::tsToChar4(char * buffer, u_int32_t ts)
{
	buffer[0] = (ts & 0xFF000000) >> 24;
	buffer[1] = (ts & 0x00FF0000) >> 16;
	buffer[2] = (ts & 0x0000FF00) >> 8;
	buffer[3] = ts & 0x000000FF;
}

std::stringstream mkvUtil::extractMKVsup(std::string filename, int index)
{
	std::stringstream out;
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
