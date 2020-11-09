/*
 * colorSpaceEndpoints.h
 *
 *  Created on: Nov 9, 2020
 *      Author: blazer
 */

#ifndef SRC_BMP_COLORSPACEENDPOINTS_H_
#define SRC_BMP_COLORSPACEENDPOINTS_H_

class colorSpaceEndpoints {
public:
	char * r;
	char * g;
	char * b;
	colorSpaceEndpoints(long long r = 0, long long g = 0, long long b = 0);
	colorSpaceEndpoints(char * r, char * g, char * b);
	virtual ~colorSpaceEndpoints();
};

#endif /* SRC_BMP_COLORSPACEENDPOINTS_H_ */
