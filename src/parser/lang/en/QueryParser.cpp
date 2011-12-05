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
	BoostParser ptp;
	this->queryTerms = ptp.parse(this->queryString);
	return this->queryTerms;
}

vector<size_t> QueryParser::fetchTermIds(){
	this->queryTermIds.erase(this->queryTermIds.begin(), this->queryTermIds.end());
	this->queryTermIds.clear();
	this->indexedTerms.erase(this->indexedTerms.begin(), this->indexedTerms.end());
	this->indexedTerms.clear();
	vector<string>::iterator itTemp;
	bool flag=false;
	bool& flagR = flag;
	size_t termId;
	for (itTemp=this->queryTerms.begin();itTemp!=this->queryTerms.end();itTemp++){
		termId = dictUtil.queryTermId(*itTemp, flagR);
		if (flagR){
			this->queryTermIds.push_back(termId);
			this->indexedTerms.push_back(*itTemp);
		}
	}
	return this->queryTermIds;
}

vector<string> QueryParser::getTerms(){
	return this->indexedTerms;
}

vector<size_t> QueryParser::getTermIds(){
	return this->queryTermIds;
}
