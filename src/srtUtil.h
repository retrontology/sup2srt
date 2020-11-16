/*
 * srtUtil.h
 *
 *  Created on: Nov 11, 2020
 *      Author: blazer
 */

#ifndef SRC_SRTUTIL_H_
#define SRC_SRTUTIL_H_

#include "pgs/pgsParser.h"
#include <sstream>

namespace srtUtil
{
	std::string milliToSRTString(double milli);
	void pgsToSRTFile(pgsParser * pgs, const char* output, const char* language, bool verbose);
	std::ostringstream pgsToSRTStream(pgsParser * pgs, const char* language, bool verbose);
};

#endif /* SRC_SRTUTIL_H_ */
