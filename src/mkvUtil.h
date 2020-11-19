/*
 * mkvUtil.h
 *
 *  Created on: Nov 14, 2020
 *      Author: blazer
 */

#ifndef SRC_MKVUTIL_H_
#define SRC_MKVUTIL_H_

#include <sstream>
#include <map>
#include <string>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

struct mkvPGS
{
	std::stringstream data;
	std::string language;
	unsigned int index;
	mkvPGS();
	mkvPGS(unsigned int index, std::string language);
	virtual ~mkvPGS();
};

namespace mkvUtil {
	void tsToChar4(char * buffer, u_int32_t ts);
	std::stringstream extractMKVsup(std::string filename, int index);
	std::map<unsigned int, std::stringstream> extractAllMKVsup(std::string filename);
	std::string formatPacket(AVPacket* packet);
};

#endif /* SRC_MKVUTIL_H_ */
