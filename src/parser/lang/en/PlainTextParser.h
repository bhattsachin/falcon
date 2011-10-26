/*
 * plainTextParser.h
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */


#ifndef PLAINTEXTPARSER_H_
#define PLAINTEXTPARSER_H_

#include "../../BaseParser.h"

class PlainTextParser: public BaseParser {
public:
	vector<string> plainRawTerms;
	PlainTextParser();
	virtual ~PlainTextParser();
	virtual void plainParseProcIpt(ifstream*);
	virtual BaseParser::SemWiki parse(string);
	virtual vector<string> plainParseProcStr(string);
	virtual void flushMe();
};


#endif /* PLAINTEXTPARSER_H_ */

