/*
 * Util.h
 *
 *  Created on: Oct 26, 2011
 *      Author: bhatt
 */

#ifndef UTIL_H_
#define UTIL_H_
#include "Library.h"

using namespace std;
class Util {
public:
	Util();
	bool parseCommandLine(int argc, char** argv);
	virtual ~Util();

};

#endif /* UTIL_H_ */
