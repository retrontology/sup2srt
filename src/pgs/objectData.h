/*
 * objectData.h
 *
 *  Created on: Nov 4, 2020
 *      Author: blazer
 */

#ifndef OBJECTDATA_H_
#define OBJECTDATA_H_

class objectData {
public:
	char * data;
	unsigned long length;
	objectData();
	objectData(char * data, long length);
	virtual ~objectData();
};

#endif /* OBJECTDATA_H_ */
