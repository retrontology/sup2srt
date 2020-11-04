/*
 * pgsUtil.h
 *
 *  Created on: Nov 3, 2020
 *      Author: blazer
 */

#ifndef PGSUTIL_H_
#define PGSUTIL_H_
namespace pgsUtil
{
unsigned long int char4ToLong(char * ptr);
unsigned int char2ToLong(char * ptr);
unsigned char cleanChar(char in);
char * subArray(char * ptr, int length, int start = 0);
}


#endif /* PGSUTIL_H_ */
