/*
 * QueryParser.h
 *
 *  Created on: Oct 30, 2011
 *      Author: Zhiliang SU
 */

#ifndef QUERYPARSER_H_
#define QUERYPARSER_H_

#include "../../BaseParser.h"
#include "../../../utilities/DictionaryUtil.h"
class QueryParser: public BaseParser {
private:
	DictionaryUtil dictUtil;
	string queryString;
	vector<string> queryTerms;
	vector<size_t> queryTermIds;
	vector<string> separateTerms();
	vector<size_t> fetchTermIds();
public:
	QueryParser();
	virtual ~QueryParser();
	void setQueryString(string);
	vector<string> getTerms();
	vector<size_t> getTermIds();
};

#endif /* QUERYPARSER_H_ */
