/*
 * PositionalTextParser.h
 *
 *  Created on: Oct 28, 2011
 *      Author: bhatt
 */

#ifndef POSITIONALTEXTPARSER_H_
#define POSITIONALTEXTPARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include "../../../utilities/FileUtil.h"

using namespace std;

class PositionalTextParser {

public:
	struct PositionalWord{
		string token;
		unsigned int position;
	};

public:
	PositionalTextParser();
	virtual ~PositionalTextParser();
	vector<PositionalWord> parse(string filepath);
private:
	void wordSplit(const string& str, const string& delim, vector<string>& parts);
};

#endif /* POSITIONALTEXTPARSER_H_ */
