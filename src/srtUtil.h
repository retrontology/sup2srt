/*
 * srtUtil.h
 *
 *  Created on: Nov 11, 2020
 *      Author: blazer
 */

#ifndef SRC_SRTUTIL_H_
#define SRC_SRTUTIL_H_

#include <string>
#include "pgs/pgsParser.h"

namespace srtUtil
{
	std::string milliToSRTString(double milli);
	void dumpBMPStrings(pgsParser * pgs, const char* language);
	void dumpTIFFStrings(pgsParser * pgs, const char* language);
	void pgsToSRT(pgsParser pgs);
};

#endif /* SRC_SRTUTIL_H_ */
