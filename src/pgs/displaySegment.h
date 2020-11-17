/*
 * displaySegment.h
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#ifndef SRC_PGS_DISPLAYSEGMENT_H_
#define SRC_PGS_DISPLAYSEGMENT_H_

#include <vector>
#include <tiffio.h>
#include <tiffio.hxx>
#include "presentationCompositionSegment.h"
#include "windowDefinitionSegment.h"
#include "paletteDefinitionSegment.h"
#include "objectDefinitionSegment.h"

class displaySegment {
public:
	presentationCompositionSegment pcs;
	std::vector<windowDefinitionSegment> wds;
	std::vector<paletteDefinitionSegment> pds;
	std::vector<objectDefinitionSegment> ods;
	pgsSegment end;
	displaySegment();
	displaySegment(presentationCompositionSegment pcs);
	displaySegment(presentationCompositionSegment pcs,
					std::vector<windowDefinitionSegment> wds,
					std::vector<paletteDefinitionSegment> pds,
					std::vector<objectDefinitionSegment> ods,
					pgsSegment end);
	virtual ~displaySegment();
	std::ostringstream getTIFF(bool gray = false);
};

#endif /* SRC_PGS_DISPLAYSEGMENT_H_ */
