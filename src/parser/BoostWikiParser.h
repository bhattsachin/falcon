/*
 * BoostWikiParser.h
 *
 *  Created on: Nov 18, 2011
 *      Author: bhatt
 */

#ifndef BOOSTWIKIPARSER_H_
#define BOOSTWIKIPARSER_H_

#include <boost/regex.hpp>
#include "BoostParser.h"

class BoostWikiParser : public BoostParser {


public:
	BoostWikiParser();
	virtual ~BoostWikiParser();
	virtual vector<string> parseFile(string path);

};

#endif /* BOOSTWIKIPARSER_H_ */
