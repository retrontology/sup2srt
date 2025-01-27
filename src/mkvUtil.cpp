#include <fstream>
#include "mkvUtil.h"
#include "pgs/pgsUtil.h"
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>
#include <time.h> 

std::map<std::string,std::string> isoMap::map
{
	{"tib", "bod"},
	{"cze", "ces"},
	{"wel", "cym"},
	{"gre", "ell"},
	{"baq", "eus"},
	{"per", "fas"},
	{"fre", "fra"},
	{"geo", "kat"},
	{"ger", "deu"},
	{"arm", "hye"},
	{"ice", "isl"},
	{"mac", "mkd"},
	{"mao", "mri"},
	{"may", "msa"},
	{"bur", "mya"},
	{"dut", "nld"},
	{"rum", "ron"},
	{"slo", "slk"},
	{"alb", "sqi"},
	{"chi", "chi_sim"}
};

supStream::supStream()
{
	this->data = std::string();
	this->track = 0;
	this->language = std::string("");
	this->title = std::string("");
	this->offset = 0;
	this->time_base = AVRational();
}

supStream::supStream(u_int32_t track, std::string language, std::string title, u_int32_t offset, AVRational time_base)
{
	this->data = std::string();
	this->track = track;
	this->language = language;
	this->title = title;
	this->offset = offset;
	this->time_base = time_base;
}

supStream::~supStream(){};


void mkvUtil::tsToChar4(char * buffer, u_int32_t ts)
{
	buffer[0] = (ts & 0xFF000000) >> 24;
	buffer[1] = (ts & 0x00FF0000) >> 16;
	buffer[2] = (ts & 0x0000FF00) >> 8;
	buffer[3] = ts & 0x000000FF;
}

std::vector<unsigned int> mkvUtil::findAllPGSTracks(std::string filename)
{
	std::vector<unsigned int> tracks;
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	for(unsigned int i = 0; i < mkvFile->nb_streams; i++)
	{
		if(mkvFile->streams[i]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			tracks.push_back(i);
		}
	}
	avformat_close_input(&mkvFile);
	return tracks;
}

std::stringstream mkvUtil::extractSingleMKVsup(std::string filename, int index)
{
	std::stringstream out;
	std::vector<unsigned int> tracks{(unsigned int)(index)};
	out << mkvUtil::extractSelectMKVsup(filename, tracks)[0].data;
	return out;
}

std::vector<supStream> mkvUtil::extractAllMKVsup(std::string filename)
{
	return mkvUtil::extractSelectMKVsup(filename, mkvUtil::findAllPGSTracks(filename));
}

std::vector<supStream> mkvUtil::extractSelectMKVsup(std::string filename, std::vector<unsigned int> tracks)
{
	std::map<unsigned int, supStream> streams;
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	u_int32_t base_offset = mkvFile->streams[0]->start_time;
	for(int i = 0; i < tracks.size(); i++)
	{
		if(mkvFile->streams[tracks[i]]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			AVDictionaryEntry* entry = NULL;
			std::string title;
			std::string language;
			u_int32_t offset;
			AVRational time_base;
			entry = av_dict_get(mkvFile->streams[tracks[i]]->metadata, "language", entry, AV_DICT_IGNORE_SUFFIX);
			if(entry == NULL) std::cerr << "Did not find language for track " + std::to_string(tracks[i]) << std::endl;
			else language = mkvUtil::cleanLangISO(std::string(entry->value));
			entry = av_dict_get(mkvFile->streams[tracks[i]]->metadata, "title", entry, AV_DICT_IGNORE_SUFFIX);
			title += entry == NULL ? language : entry->value;
			//offset = mkvFile->streams[tracks[i]]->start_time;
			time_base.num = mkvFile->streams[tracks[i]]->time_base.num * 90;
			time_base.den = mkvFile->streams[tracks[i]]->time_base.den;
			streams.insert(std::pair<unsigned int, supStream>(tracks[i], supStream(tracks[i], language, title, base_offset, time_base)));
		}
		else std::cerr << "Track " + std::to_string(tracks[i]) + " is not a PGS stream!" << std::endl;
	}
	AVPacket * packet = av_packet_alloc();
	std::cout << std::endl;
	time_t now;
	time(&now);
	time_t last_time = now;
	unsigned long oldpts;
	while (av_read_frame(mkvFile, packet) >= 0)
	{
		unsigned int num = packet->stream_index;
		if (streams.find(num) != streams.end())
		{
			streams[packet->stream_index].data += mkvUtil::formatPacket(packet, streams[packet->stream_index]);
			if(packet->pts != oldpts)
			{
				time(&now);
				if (now - last_time >= 1)
				{
					std::cout << "\rParsing mkv at: " + mkvUtil::milliToString((packet->pts - streams[packet->stream_index].offset) * (streams[packet->stream_index].time_base.num / 90) * 1000 / streams[packet->stream_index].time_base.den);
					std::cout.flush();
					last_time = now;
				}
				oldpts = packet->pts;
			}
		}
		av_packet_unref(packet);
	}
	std::cout << std::endl;
	avformat_close_input(&mkvFile);
	av_packet_free(&packet);
	std::vector<supStream> out;
	for(std::map<unsigned int, supStream>::iterator it = streams.begin(); it != streams.end(); it++) out.push_back(it->second);
	return out;
}

void mkvUtil::dumpSingleMKVsup(std::string filename, int index)
{
	std::stringstream out;
	std::vector<unsigned int> tracks{(unsigned int)(index)};
	out << mkvUtil::extractSelectMKVsup(filename, tracks)[0].data;
}

void mkvUtil::dumpAllMKVsup(std::string filename)
{
	mkvUtil::dumpSelectMKVsup(filename, mkvUtil::findAllPGSTracks(filename));
}

void mkvUtil::dumpSelectMKVsup(std::string filename, std::vector<unsigned int> tracks)
{
	std::map<unsigned int, std::ofstream> streams;
	std::string basename = filename.substr(0, filename.find_last_of('.') + 1);
	AVFormatContext * mkvFile = avformat_alloc_context();
	avformat_open_input(&mkvFile, filename.c_str(), NULL, NULL);
	avformat_find_stream_info(mkvFile,  NULL);
	for(int i = 0; i < tracks.size(); i++)
	{
		if(mkvFile->streams[tracks[i]]->codecpar->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
		{
			AVDictionaryEntry* entry = NULL;
			std::string title;
			std::string language;
			entry = av_dict_get(mkvFile->streams[tracks[i]]->metadata, "language", entry, AV_DICT_IGNORE_SUFFIX);
			if(entry == NULL) std::cerr << "Did not find language for track " + std::to_string(tracks[i]) << std::endl;
			else language = mkvUtil::cleanLangISO(std::string(entry->value));
			entry = av_dict_get(mkvFile->streams[tracks[i]]->metadata, "title", entry, AV_DICT_IGNORE_SUFFIX);
			title += entry == NULL ? language : entry->value;
			std::string outname = basename + std::to_string(tracks[i]) + ".";
			if(language.compare("") != 0) outname += language + ".sup";
			else outname += "sup";
			streams.insert(std::pair<unsigned int, std::ofstream>(tracks[i], std::ofstream(outname, std::ofstream::binary)));
		}
		else std::cerr << "Track " + std::to_string(tracks[i]) + " is not a PGS stream!" << std::endl;
	}
	AVPacket * packet = av_packet_alloc();
	time_t now;
	time(&now);
	time_t last_time = now;
	while (av_read_frame(mkvFile, packet) >= 0)
	{
		unsigned int num = packet->stream_index;
		if (streams.find(num) != streams.end())
		{
			streams[packet->stream_index] << mkvUtil::formatPacket(packet, mkvFile->streams[0]->start_time, mkvFile->streams[0]->time_base);
			time(&now);
			if (now - last_time >= 1)
			{
				std::cout << "\rParsing mkv at: " + mkvUtil::milliToString((packet->pts - mkvFile->streams[0]->start_time) * mkvFile->streams[0]->time_base.num * 1000 / mkvFile->streams[0]->time_base.den);
				std::cout.flush();
				last_time = now;
			}
		}
		av_packet_unref(packet);
	}
	avformat_close_input(&mkvFile);
	av_packet_free(&packet);
	for(std::map<unsigned int, std::ofstream>::iterator it = streams.begin(); it != streams.end(); it++) it->second.close();
}

std::string mkvUtil::cleanLangISO(std::string in)
{
	std::string out;
	std::map<std::string, std::string>::iterator it = isoMap::map.find(in);
	if(it != isoMap::map.end()) out = it->second;
	else out = in;
	return out;
}

std::vector<unsigned int> mkvUtil::parseTracks(std::string trackString)
{
	std::vector<unsigned int> out;
	if(trackString.find(',') < trackString.length())
	{
		std::stringstream stream(trackString);
		while(stream.good())
		{
			std::string substr;
			std::getline(stream, substr, ',');
			if(substr.find('-') < substr.length())
			{
				std::stringstream range(substr);
				std::string start;
				std::string end;
				std::getline(range, start, '-');
				std::getline(range, end);
				for(unsigned int i = atoi(start.c_str()); i <= atoi(end.c_str()); i++)
				{
					out.push_back(i);
				}
			}
			else out.push_back(atoi(substr.c_str()));
		}
	}
	else
	{
		out.push_back(atoi(trackString.c_str()));
	}
	return out;
}

std::string mkvUtil::formatPacket(AVPacket* packet, u_int32_t base_offset, AVRational time_base)
{
	std::ostringstream out;
	int offset = 0;
	while(offset < packet->size)
	{
		unsigned int segSize = mkvUtil::char2ToInt(reinterpret_cast<char *>(packet->data + offset + 1));
		out << "PG";
		char * buffer = new char[4];
		u_int32_t pts = floor((packet->pts - base_offset) * time_base.num * 1000 / time_base.den);
		u_int32_t dts = floor((packet->dts - base_offset) * time_base.num * 1000 / time_base.den);
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

std::string mkvUtil::formatPacket(AVPacket* packet, supStream stream)
{
	std::ostringstream out;
	int offset = 0;
	while(offset < packet->size)
	{
		unsigned int segSize = mkvUtil::char2ToInt(reinterpret_cast<char *>(packet->data + offset + 1));
		out << "PG";
		char * buffer = new char[4];
		u_int32_t pts = floor((packet->pts - stream.offset) * stream.time_base.num * 1000 / stream.time_base.den);
		u_int32_t dts = floor((packet->dts - stream.offset) * stream.time_base.num * 1000 / stream.time_base.den);
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

std::string mkvUtil::milliToString(unsigned long in)
{
	unsigned long temp = floor(in);
	int hour = floor(temp / 3600000);
	int minute = floor((temp % 3600000) / 60000);
	int second = floor((temp % 60000) / 1000);
	int milli = floor((temp % 1000) / 10);
	std::ostringstream h;
	std::ostringstream min;
	std::ostringstream s;
	std::ostringstream mil;
	h << std::setw(2) << std::setfill('0') << std::to_string(hour);
	min << std::setw(2) << std::setfill('0') << std::to_string(minute);
	s << std::setw(2) << std::setfill('0') << std::to_string(second);
	mil << std::setw(2) << std::setfill('0') << std::to_string(milli);
	return std::string(h.str() + ":" + min.str() + ":" + s.str() + "." + mil.str());
}

unsigned int mkvUtil::char2ToInt(char * ptr)
{
	return mkvUtil::cleanChar(ptr[1]) | (mkvUtil::cleanChar(ptr[0]) << 8);
}

unsigned char mkvUtil::cleanChar(char in)
{
	return static_cast<unsigned int>(in) ;
}
