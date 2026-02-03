#include "srtUtil.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include "pgs/pgsUtil.h"
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
			double startMs = pgs->displaySegments[i].pcs.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			double endMs = pgs->displaySegments[i].end.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			if (endMs <= startMs && (i + 1) < pgs->displaySegments.size())
			{
				endMs = pgs->displaySegments[i + 1].pcs.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			}
			if (endMs <= startMs)
			{
				endMs = startMs + 1000.0;
			}
			std::string start = srtUtil::milliToSRTString(startMs);
			std::string end = srtUtil::milliToSRTString(endMs);
			std::ostringstream data = pgs->displaySegments[i].getClearTIFF();
			Pix * pix = pixReadMem(reinterpret_cast<const unsigned char *>(data.str().c_str()), data.str().length());
			data.clear();
			pixSetResolution(pix, 300, 300);
			api->SetImage(pix);
			api->Recognize(0);
			//char * tessString = api->GetUTF8Text();
			//std::string text(tessString);
			//delete[] tessString;
			std::string text = srtUtil::readFormattedString(api);
			std::ostringstream buffer;
			buffer << std::to_string(count) << std::endl;
			buffer << start + " --> " + end << std::endl;
			buffer << text << std::endl;
			out << buffer.str();
			if(verbose) std::cout << buffer.str();
			pixDestroy(&pix);
			count++;
		}
	}
	out.close();
	delete api;
}

std::string srtUtil::readFormattedString(tesseract::TessBaseAPI * api)
{
	std::string text("");
	tesseract::ResultIterator* iter = api->GetIterator();
	tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
	bool* is_bold = new bool;
	bool* is_italic = new bool;
	bool* is_underlined = new bool;
	bool* is_monospace = new bool;
	bool* is_serif = new bool;
	bool* is_smallcaps = new bool;
	int* pointsize = new int;
	int* font_id = new int;
	bool prevItalic = false;
	if(iter != 0)
	{
		do
		{
			const char* buffer = iter->GetUTF8Text(level);
			if(buffer)
			{
				std::string word(buffer);
				for(int i = 0; i < word.size(); i++)
				{
					switch (word[i])
					{
						case '|':
						{
							word[i] = 'I';
							break;
						}
					}
				}
				iter->WordFontAttributes(is_bold, is_italic, is_underlined, is_monospace, is_serif, is_smallcaps, pointsize, font_id);
				if(!prevItalic && *is_italic)
				{
					text += "<i>";
				}
				text += word;
				if(!iter->IsAtFinalElement(tesseract::RIL_TEXTLINE, level))
				{
					text += " ";
					prevItalic = *is_italic;
				}
				else
				{
					if(*is_italic)
					{
						text += "</i>";
					}
					text += "\n";
					prevItalic = false;
				}
			}
			delete[] buffer;
		}while(iter->Next(level));
	}
	delete iter, is_bold, is_italic, is_underlined, is_monospace, is_serif, is_smallcaps, pointsize, font_id;
	return text;
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
			double startMs = pgs->displaySegments[i].pcs.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			double endMs = pgs->displaySegments[i].end.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			if (endMs <= startMs && (i + 1) < pgs->displaySegments.size())
			{
				endMs = pgs->displaySegments[i + 1].pcs.HEADER.PRESENTATION_TIMESTAMP / static_cast<double>(pgsUtil::PGS_TICKS_PER_MS);
			}
			if (endMs <= startMs)
			{
				endMs = startMs + 1000.0;
			}
			std::string start = srtUtil::milliToSRTString(startMs);
			std::string end = srtUtil::milliToSRTString(endMs);
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
