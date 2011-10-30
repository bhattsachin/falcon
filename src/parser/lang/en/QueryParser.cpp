/*
 * QueryParser.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: Zhiliang SU
 */

#include "QueryParser.h"

QueryParser::QueryParser() {
	// TODO Auto-generated constructor stub

}

QueryParser::~QueryParser() {
	// TODO Auto-generated destructor stub
}

void QueryParser::setQueryString(string querystr){
	this->queryString = querystr;
	this->separateTerms();
	this->fetchTermIds();
}

vector<string> QueryParser::separateTerms(){
	vector<string>& queryTermsR = queryTerms;
	const string& queryStrR=this->queryString;
	const string& queryDelimaR=" ";
	baseToolSplit(queryStrR,queryDelimaR,queryTermsR);
	return queryTerms;
}

vector<size_t> QueryParser::fetchTermIds(){
	vector<string>::iterator itTemp;
	baseParseProc(queryTerms);
	for (itTemp=semwiki.baseParsedTerms.begin();itTemp!=semwiki.baseParsedTerms.end();itTemp++){
		queryTermIds.push_back(dictUtil.getTermDictionaryTermId(*itTemp));
	}
	return queryTermIds;
}

vector<string> QueryParser::getTerms(){
	return semwiki.baseParsedTerms;
}

vector<size_t> QueryParser::getTermIds(){
	return queryTermIds;
}
