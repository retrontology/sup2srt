#ifndef SRC_MKVUTIL_H_
#define SRC_MKVUTIL_H_

#include <sstream>
#include <vector>
#include <string>
#include <map>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

struct isoMap
{
	static std::map<std::string,std::string> map;
};

struct supStream
{
public:
	std::string data;
	std::string language;
	std::string title;
	unsigned int track;
	supStream();
	supStream(unsigned int track, std::string language, std::string title);
	virtual ~supStream();
};

namespace mkvUtil
{
	void tsToChar4(char * buffer, u_int32_t ts);
	std::vector<unsigned int> findAllPGSTracks(std::string filename);
	std::stringstream extractSingleMKVsup(std::string filename, int index);
	std::vector<supStream> extractSelectMKVsup(std::string filename, std::vector<unsigned int> tracks);
	std::vector<supStream> extractAllMKVsup(std::string filename);
	void dumpSingleMKVsup(std::string filename, int index);
	void dumpAllMKVsup(std::string filename);
	void dumpSelectMKVsup(std::string filename, std::vector<unsigned int> tracks);
	std::string cleanLangISO(std::string in);
	std::vector<unsigned int> parseTracks(std::string trackString);
	std::string formatPacket(AVPacket* packet, float_t time_coeff);
	std::string milliToString(unsigned long in);
	unsigned int char2ToInt(char * ptr);
	unsigned char cleanChar(char in);
};

#endif /* SRC_MKVUTIL_H_ */
