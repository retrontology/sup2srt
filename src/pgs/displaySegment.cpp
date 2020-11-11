/*
 * displaySegment.cpp
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

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

bitmap displaySegment::getBitmap()
{
	bitmapColorTable ct = this->pds[0].getColorTable();
	char * data = this->ods[0].data;
	bitmapDIBHeaderV4 dib = bitmapDIBHeaderV4(this->ods[0].width, this->ods[0].height, this->ods[0].objectDataLength, ct.length*4);
	unsigned long fileSize = (BITMAP_FILEHEADER_SIZE + ct.length*4 + this->ods[0].objectDataLength + dib.size);
	unsigned long offset = ((BITMAP_FILEHEADER_SIZE + ct.length*4 + dib.size));
	bitmapFileHeader fh = bitmapFileHeader(BM, fileSize, 0, 0, offset);
	return bitmap(fh, dib, ct, data);
}
