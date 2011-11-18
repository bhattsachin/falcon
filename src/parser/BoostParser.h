/*
 * BoostParser.h
 *
 *  Created on: Nov 17, 2011
 *      Author: bhatt
 */

#ifndef BOOSTPARSER_H_
#define BOOSTPARSER_H_

#include "../utilities/Library.h";
#include "../utilities/FileUtil.h"

using namespace std;
using namespace boost;

class BoostParser {
public:
	vector<string> stop_words;
	BoostParser();
	virtual ~BoostParser();

	virtual vector<string> parseFile(string path);
	virtual vector<string> parse(string text);
	void init(string stopWordsFile);

};

#endif /* BOOSTPARSER_H_ */
