/*
 * BaseParser.h
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */

#ifndef BASEPARSER_H_
#define BASEPARSER_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;


class BaseParser {
public:
	string tempSection;
	struct SemWiki {
		vector<string> wikiInternLink;
		vector<string> wikiCategory;
		vector<string> wikiInfobox;
		vector<string> wikiTaxobox;
		vector<string> wikiSection;
		string wikiArticalName;
		string wikiAuthor;
		string wikiTimeStamp;
		vector<string> baseParsedTerms;
	};

	SemWiki semwiki;

	BaseParser();
	string stwListPath;
	virtual void initParser(string);
	virtual ~BaseParser();
	virtual void baseParseProc(vector<string> );
	virtual SemWiki parse(string path);
	virtual void baseParserInit();
	virtual void baseToolSplit(const string&, const string&, vector<string>&);
	virtual void flushMe();
	vector<string> addTerms;

private:
	vector<string> stwList;
	vector<int> charExclude;
	virtual string baseNum(string);
	virtual string basePunc(string);
	virtual string baseCase(string);
	//virtual bool baseSTW(string);
	virtual void baseSTW();
	virtual string baseHyphen(string);
	virtual string baseStem(string);

};

#endif /* BASEPARSER_H_ */
