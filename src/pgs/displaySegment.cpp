/*
 * displaySegment.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#include "displaySegment.h"

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

bitmap displaySegment::getBitmap()
{
	bitmapColorTable ct = pds[0].getColorTable();
	objectData data = ods[0].data;
	bitmapDIBHeaderV4 dib = bitmapDIBHeaderV4(ods[0].width, ods[0].height, data.length, ct.length*4);
	unsigned long fileSize = (BITMAP_FILEHEADER_SIZE + ct.length + data.length + dib.size);
	unsigned long offset = ((BITMAP_FILEHEADER_SIZE + ct.length + dib.size));
	bitmapFileHeader fh = bitmapFileHeader(BM, fileSize, 0, 0, offset);
	return bitmap(fh, dib, ct, data.data);
}

