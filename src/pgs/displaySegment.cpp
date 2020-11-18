/*
 * displaySegment.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#include <tiffio.h>
#include <tiffio.hxx>
#include <sstream>
#include <iostream>
#include "displaySegment.h"
#include "pgsUtil.h"

displaySegment::displaySegment()
{

}

displaySegment::displaySegment(presentationCompositionSegment pcs)
{
	this->pcs = pcs;
}

displaySegment::displaySegment(presentationCompositionSegment pcs, std::vector<windowDefinitionSegment> wds, std::vector<paletteDefinitionSegment> pds, std::vector<objectDefinitionSegment> ods, pgsSegment end) {
	this->pcs = pcs;
	this->wds = wds;
	this->pds = pds;
	this->ods = ods;
	this->end = end;
}

displaySegment::~displaySegment() {

}

std::ostringstream displaySegment::getTIFF(bool gray)
{
	int samples;
	gray ? samples = 3 : samples = 4;
	std::ostringstream tiffStream;
	TIFF* out = TIFFStreamOpen(std::to_string(this->ods[0].objectID).c_str(), &tiffStream);
	TIFFSetField (out, TIFFTAG_IMAGEWIDTH, this->ods[0].width);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH, this->ods[0].height);
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samples);
	TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	TIFFSetField(out, TIFFTAG_XRESOLUTION, 300);
	TIFFSetField(out, TIFFTAG_YRESOLUTION, 300);
	TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, this->ods[0].width*samples);
	unsigned char* buffer = (unsigned char*)_TIFFmalloc(this->ods[0].width*samples);
	unsigned long ** pixels = new unsigned long * [this->ods[0].height];
	for(int i = 0; i < this->ods[0].height; i++){ pixels[i] = new unsigned long[this->ods[0].width]; }
	pgsUtil::decodeRLE(pixels, this->pds[0], this->ods[0], gray);
	char * temp = new char[this->ods[0].width*samples];
	for (int i = 0; i < ods[0].height; i++)
	{
		for(int j = 0; j < this->ods[0].width; j++)
		{
			pgsUtil::numToChars(temp+j*samples, pixels[i][j], samples);
		}
	    memcpy(buffer, temp, this->ods[0].width*samples);
	    if (TIFFWriteScanline(out, buffer, i) < 0) break;
	}
	delete[] temp;
	for(int i = 0; i < ods[0].height; i++)
	{
		delete[] pixels[i];
	}
	delete[] pixels;
	TIFFClose(out);
	_TIFFfree(buffer);
	return tiffStream;
}

std::ostringstream displaySegment::getClearTIFF()
{
	int samples = 3;
	std::ostringstream tiffStream;
	TIFF* out = TIFFStreamOpen(std::to_string(this->ods[0].objectID).c_str(), &tiffStream);
	TIFFSetField (out, TIFFTAG_IMAGEWIDTH, this->ods[0].width+4);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH, this->ods[0].height+4);
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samples);
	TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
	TIFFSetField(out, TIFFTAG_XRESOLUTION, 300);
	TIFFSetField(out, TIFFTAG_YRESOLUTION, 300);
	TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, (this->ods[0].width+4)*samples);
	unsigned char* buffer = (unsigned char*)_TIFFmalloc((this->ods[0].width+4)*samples);
	unsigned long ** pixels = new unsigned long * [this->ods[0].height];
	for(int i = 0; i < this->ods[0].height; i++){ pixels[i] = new unsigned long[this->ods[0].width]; }
	pgsUtil::decodeRLE(pixels, this->pds[0], this->ods[0], true);
	char * temp = new char[(this->ods[0].width+4)*samples];
	for (int i = 0; i < ods[0].height+4; i++)
	{
		for(int j = 0; j < this->ods[0].width+4; j++)
		{
			if(i == 0 || i == 1 || i == ods[0].height+2 || i == ods[0].height+3 || j == 0 || j == 1 || j == ods[0].width+2 || j == ods[0].width+3)
			{
				pgsUtil::numToChars(temp+j*samples, 0xFFFFFF, samples);
			}
			else
			{
				pgsUtil::numToChars(temp+j*samples, pixels[i-2][j-2], samples);
			}

		}
	    memcpy(buffer, temp, (this->ods[0].width+4)*samples);
	    if (TIFFWriteScanline(out, buffer, i) < 0) break;
	}
	delete[] temp;
	for(int i = 0; i < ods[0].height; i++)
	{
		delete[] pixels[i];
	}
	delete[] pixels;
	TIFFClose(out);
	_TIFFfree(buffer);
	return tiffStream;
}

