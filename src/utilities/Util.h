/*
 * Util.h
 *
 *  Created on: Oct 26, 2011
 *      Author: bhatt
 */

#ifndef UTIL_H_
#define UTIL_H_
#include "Library.h"
#include<map>
#include "FileUtil.h"

using namespace std;
using namespace boost;
class Util {
	public: map<string, string> fileMap;
public:
	Util();
	bool parseCommandLine(int argc, char** argv);
	virtual ~Util();
	void loadFileDictionary();

};

#endif /* UTIL_H_ */
