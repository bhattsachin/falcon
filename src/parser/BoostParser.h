/*
 * BoostParser.h
 *
 *  Created on: Nov 17, 2011
 *      Author: bhatt
 */

#ifndef BOOSTPARSER_H_
#define BOOSTPARSER_H_

#include "../utilities/Library.h"
#include "../utilities/FileUtil.h"

using namespace std;
using namespace boost;

class BoostParser {

public:
	struct ParsedDocument{
	vector<string> tokens;
	string articleName;
	string author;
	string timestamp;
	vector<string> infobox;
	vector<vector<string> > sections;
	vector<string> links;
	vector<string> category;

};

public:
	vector<string> stop_words;
	BoostParser();
	virtual ~BoostParser();

	virtual ParsedDocument parseFile(string path);
	virtual vector<string> parse(string text);
	void init(string stopWordsFile);


};

#endif /* BOOSTPARSER_H_ */
