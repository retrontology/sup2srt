/*
 * srtUtil.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: blazer
 */

#include "srtUtil.h"
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

void srtUtil::pgsToSRTFile(pgsParser * pgs, const char* output, const char* language, bool verbose)
{
	std::ofstream out;
	out.open(output);
	tesseract::TessBaseAPI * api = new tesseract::TessBaseAPI();
	if (api->Init(NULL, language))
	{
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	int count = 1;
	for(int i = 0; i < pgs->displaySegments.size(); i++)
	{
		if(pgs->displaySegments[i].ods.size()==1 && pgs->displaySegments[i].pds.size()==1)
		{
			std::string start = srtUtil::milliToSRTString(pgs->displaySegments[i].pcs.HEADER.PRESENTATION_TIMESTAMP/90);
			std::string end = srtUtil::milliToSRTString(pgs->displaySegments[i+1].pcs.HEADER.PRESENTATION_TIMESTAMP/90);
			std::ostringstream data = pgs->displaySegments[i].getTIFF();
			Pix * pix = pixReadMem(reinterpret_cast<const unsigned char *>(data.str().c_str()), data.str().length());
			pixSetResolution(pix, 70, 70);
			api->SetImage(pix);
			std::string text(api->GetUTF8Text());
			for(int i = 0; i < text.size(); i++)
			{
				switch (text[i])
				{
					case '|':
					{
						text[i] = 'I';
						break;
					}
				}
			}
			std::ostringstream buffer;
			buffer << std::to_string(count) << std::endl;
			buffer << start + " --> " + end << std::endl;
			buffer << text << std::endl << std::endl;
			out << buffer.str();
			if(verbose) std::cout << buffer.str();
			pixDestroy(&pix);

			count++;
		}
	}
	out.close();
	delete api;
}

std::ostringstream srtUtil::pgsToSRTStream(pgsParser * pgs, const char* language, bool verbose)
{
	std::ostringstream out;
	tesseract::TessBaseAPI * api = new tesseract::TessBaseAPI();
	if (api->Init(NULL, language))
	{
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	int count = 1;
	for(int i = 0; i < pgs->displaySegments.size(); i++)
	{
		if(pgs->displaySegments[i].ods.size()==1 && pgs->displaySegments[i].pds.size()==1)
		{
			std::string start = srtUtil::milliToSRTString(pgs->displaySegments[i].pcs.HEADER.PRESENTATION_TIMESTAMP/90);
			std::string end = srtUtil::milliToSRTString(pgs->displaySegments[i+1].pcs.HEADER.PRESENTATION_TIMESTAMP/90);
			std::ostringstream data = pgs->displaySegments[i].getTIFF();
			Pix * pix = pixReadMem(reinterpret_cast<const unsigned char *>(data.str().c_str()), data.str().length());
			pixSetResolution(pix, 70, 70);
			api->SetImage(pix);
			std::string text(api->GetUTF8Text());
			for(int i = 0; i < text.size(); i++)
			{
				switch (text[i])
				{
					case '|':
					{
						text[i] = 'I';
						break;
					}
				}
			}
			out << std::to_string(count) << std::endl;
			out << start + " --> " + end << std::endl;
			out << text << std::endl << std::endl;

			pixDestroy(&pix);

			count++;
		}
	}
	delete api;
	return out;
}
