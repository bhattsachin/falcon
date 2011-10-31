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
	bool existFlag;
	size_t termId;

	bool& flagR = existFlag;
	for (itTemp=semwiki.baseParsedTerms.begin();itTemp!=semwiki.baseParsedTerms.end();itTemp++){
		existFlag = false;
		termId = dictUtil.queryTermId(*itTemp, flagR);
		if(flagR){
			queryTermIds.push_back(termId);
		}


	}
	return queryTermIds;
}

vector<string> QueryParser::getAvailableQueryTerms(string query){
	setQueryString(query);


	vector<string>::iterator itTemp;
		baseParseProc(queryTerms);
		bool existFlag;
		size_t termId;

		bool& flagR = existFlag;
		for (itTemp=semwiki.baseParsedTerms.begin();itTemp!=semwiki.baseParsedTerms.end();itTemp++){
			existFlag = false;
			termId = dictUtil.queryTermId(*itTemp, flagR);
			if(flagR){
				queryTermIds.push_back(termId);
			}


	}

}


vector<string> QueryParser::getTerms(){
	return semwiki.baseParsedTerms;
}

vector<size_t> QueryParser::getTermIds(){
	return queryTermIds;
}
