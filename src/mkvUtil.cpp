#include "mkvUtil.h"
#include "pgs/pgsUtil.h"
#include <map>
#include <utility>
#include <iostream>


supStream::supStream()
{
	this->data = std::string();
	this->track = 0;
	this->language = std::string("");
	this->title = std::string("");
}

supStream::supStream(unsigned int track, std::string language, std::string title)
{
	this->data = std::string();
	this->track = track;
	this->language = language;
	this->title = title;
}

supStream::~supStream(){};


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

std::vector<supStream> mkvUtil::extractAllMKVsup(std::string filename)
{
	std::map<unsigned int, supStream> streams;
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	for(unsigned int i = 0; i < mkvFile->nb_streams; i++)
	{
		if(mkvFile->streams[i]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			AVDictionaryEntry* entry = NULL;
			entry = av_dict_get(mkvFile->streams[i]->metadata, "language", entry, AV_DICT_IGNORE_SUFFIX);
			std::string language(entry->value);
			entry = av_dict_get(mkvFile->streams[i]->metadata, "title", entry, AV_DICT_IGNORE_SUFFIX);
			std::string title(entry->value);
			streams.insert(std::pair<unsigned int, supStream>(i, supStream(i, language, title)));
		}
	}
	AVPacket * packet = av_packet_alloc();
	while (av_read_frame(mkvFile, packet) >= 0)
	{
		if (mkvFile->streams[packet->stream_index]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			streams[packet->stream_index].data += mkvUtil::formatPacket(packet);
		}
		av_packet_unref(packet);
	}
	avformat_close_input(&mkvFile);
	av_packet_free(&packet);
	std::vector<supStream> out;
	for(std::map<unsigned int, supStream>::iterator it = streams.begin(); it != streams.end(); it++) out.push_back(it->second);
	return out;
}

void mkvUtil::dumpAllMKVsup(std::string filename)
{
	std::map<unsigned int, std::ofstream> streams;
	std::string basename = filename.substr(0, filename.find_last_of('.') + 1);
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	for(unsigned int i = 0; i < mkvFile->nb_streams; i++)
	{
		if(mkvFile->streams[i]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			AVDictionaryEntry* entry = NULL;
			entry = av_dict_get(mkvFile->streams[i]->metadata, "language", entry, AV_DICT_IGNORE_SUFFIX);
			std::string language(entry->value);
			entry = av_dict_get(mkvFile->streams[i]->metadata, "title", entry, AV_DICT_IGNORE_SUFFIX);
			std::string title(entry->value);
			std::string outname = basename + std::to_string(i) + "." + title + "." + language + ".sup";
			streams.insert(std::pair<unsigned int, std::ofstream>(i, std::ofstream(outname, std::ofstream::binary)));
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
	for(std::map<unsigned int, std::ofstream>::iterator it = streams.begin(); it != streams.end(); it++) it->second.close();
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
