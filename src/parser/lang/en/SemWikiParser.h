/*
 * SemWikiParser.h
 *
 *  Created on: Oct 2, 2011
 *      Author: suz
 */

#ifndef SEMWIKIPARSER_H_
#define SEMWIKIPARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

class SemWikiParser {
public:
	struct swParsedTerm{
		string swTerm;
		int	swType;
	};
	SemWikiParser();
	virtual ~SemWikiParser();
	vector<swParsedTerm> parse(string filepath);
private:
	vector<swParsedTerm> swTerms;
	int typeCode;
	int procCode;
	bool readFile(string);
	virtual string basePunc(string);
	virtual string baseHyphen(string);
	virtual void baseToolSplit(const string& , const string& , vector<string>& );
	virtual int findType(string);
};

#endif /* SEMWIKIPARSER_H_ */
