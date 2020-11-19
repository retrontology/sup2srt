/*
 * mkvUtil.cpp
 *
 *  Created on: Nov 14, 2020
 *      Author: blazer
 */

#include "mkvUtil.h"
#include "pgs/pgsUtil.h"


mkvPGS::mkvPGS()
{
	this->data = std::stringstream();
	this->index = 0;
	this->language = std::string("");
}

mkvPGS::mkvPGS(unsigned int index, std::string language)
{
	this->data = std::stringstream();
	this->index = index;
	this->language = language;
}

mkvPGS::~mkvPGS(){};


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
			out << mkvUtil::formatPacket(packet);
		}
		av_packet_unref(packet);
	}
	avformat_close_input(&mkvFile);
	av_packet_free(&packet);
	return out;
}

std::map<unsigned int, std::stringstream> mkvUtil::extractAllMKVsup(std::string filename)
{
	std::map<unsigned int, std::stringstream> streams;
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	for(int i = 0; i < mkvFile->nb_streams; i++)
	{
		if(mkvFile->streams[i]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			streams.insert(std::pair<int, std::stringstream>(i, std::stringstream()));
		}
	}
	AVPacket * packet = av_packet_alloc();
	while (av_read_frame(mkvFile, packet) >= 0)
	{
		if (mkvFile->streams[packet->stream_index]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			streams[packet->stream_index] << mkvUtil::formatPacket(packet);
		}
		av_packet_unref(packet);
	}
	avformat_close_input(&mkvFile);
	av_packet_free(&packet);
	return streams;
}

std::string mkvUtil::formatPacket(AVPacket* packet)
{
	std::ostringstream out;
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
		delete[] buffer;
		out << std::string(reinterpret_cast<char *>(packet->data + offset), segSize + 3);
		offset += 3 + segSize;
	}
	return out.str();
}
