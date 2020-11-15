/*
 * mkvUtil.h
 *
 *  Created on: Nov 14, 2020
 *      Author: blazer
 */

#ifndef SRC_MKVUTIL_H_
#define SRC_MKVUTIL_H_

#include <sstream>

namespace mkvUtil {
	void tsToChar4(char * buffer, u_int32_t ts);
	std::stringstream extractMKVsup(std::string filename, int index);
};

#endif /* SRC_MKVUTIL_H_ */
