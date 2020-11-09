/*
 * pgsImage.h
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#ifndef SRC_PGS_PGSIMAGE_H_
#define SRC_PGS_PGSIMAGE_H_

#include "displaySegment.h"

class pgsImage {
public:
	displaySegment ds;
	pgsImage(displaySegment ds);
	virtual ~pgsImage();
};

#endif /* SRC_PGS_PGSIMAGE_H_ */
