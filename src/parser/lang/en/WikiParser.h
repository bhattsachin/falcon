/*
 * WikiParser.h
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */

#ifndef WIKIPARSER_H_
#define WIKIPARSER_H_

#include "PlainTextParser.h"
#include <deque>
class WikiParser: public PlainTextParser {
public:

	WikiParser();
	virtual ~WikiParser();
	virtual SemWiki parse(string);
	virtual void initParserWiki(string);
	virtual void flushMe();
private:
	bool taxoHold;
	bool infoHold;
	bool sectHold;
	int sectWordCount;
	struct SemWikiFlags{
		bool cat;
		bool artName;
		bool author;
		bool timeStamp;
		bool internalLink;
		bool section;
		bool infoBox;
		bool taxoBox;

	};

	SemWikiFlags semWikiFlags;

	virtual void wikiExtractMeta(string);
	virtual void wikiGetCat(string);
	virtual void wikiGetArtName(string);
	virtual void wikiGetAuthor(string);
	virtual void wikiGetTimeStamp(string);
	virtual void wikiGetInternLink(string);
	virtual void wikiGetSection(string);
	virtual void wikiGetInfobox(string);
	virtual void wikiGetTaxobox(string);
	virtual string wikiToolReplace(string, char, char);
	virtual deque<int> wikiToolFindMkup(string, string, string);

};

#endif /* WIKIPARSER_H_ */
