/*
 * srtUtil.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: blazer
 */

#include "srtUtil.h"
#include "bmp/bitmap.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

std::string srtUtil::milliToSRTString(double in)
{
	unsigned long temp = floor(in);
	int hour = floor(temp / 3600000);
	int minute = floor((temp % 3600000) / 60000);
	int second = floor((temp % 60000) / 1000);
	int milli = floor(temp % 1000);
	std::ostringstream h;
	std::ostringstream min;
	std::ostringstream s;
	std::ostringstream mil;
	h << std::setw(2) << std::setfill('0') << std::to_string(hour);
	min << std::setw(2) << std::setfill('0') << std::to_string(minute);
	s << std::setw(2) << std::setfill('0') << std::to_string(second);
	mil << std::setw(3) << std::setfill('0') << std::to_string(milli);
	return std::string(h.str() + ":" + min.str() + ":" + s.str() + "," + mil.str());
}

void srtUtil::dumpBMPStrings(pgsParser * pgs, const char* language)
{
    tesseract::TessBaseAPI * api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, language))
    {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	int count = 0;
	for(int i = 0; i < pgs->displaySegments.size(); i++)
	{
		if(pgs->displaySegments[i].ods.size()==1 && pgs->displaySegments[i].pds.size()==1)
		{
			bitmap bmp = pgs->displaySegments[i].getBitmap();
			char * data = new char[bmp.fileHeader.fileSize];
			bmp.getByteArray(data);
			Pix * pix = pixReadMem(reinterpret_cast<unsigned char *>(data), bmp.fileHeader.fileSize);
			api->SetImage(pix);
			std::cout << std::to_string(count) + ": " + api->GetUTF8Text() << std::endl;
			count++;
		}
	}
}

void srtUtil::pgsToSRT(pgsParser pgs)
{

}
