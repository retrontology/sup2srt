#ifndef SRC_MKVUTIL_H_
#define SRC_MKVUTIL_H_

#include <sstream>
#include <vector>
#include <string>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

struct supStream
{
	std::string data;
	std::string language;
	std::string title;
	unsigned int track;
	supStream();
	supStream(unsigned int track, std::string language, std::string title);
	virtual ~supStream();
};

namespace mkvUtil {
	void tsToChar4(char * buffer, u_int32_t ts);
	std::stringstream extractMKVsup(std::string filename, int index);
	std::vector<supStream> extractAllMKVsup(std::string filename);
	void dumpAllMKVsup(std::string filename);
	std::string formatPacket(AVPacket* packet);
};

#endif /* SRC_MKVUTIL_H_ */
