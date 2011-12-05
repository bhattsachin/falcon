/*
 * ForwardIndex.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: suz
 */

#include "ForwardIndex.h"

ForwardIndex::ForwardIndex() {
	// TODO Auto-generated constructor stub

}

ForwardIndex::~ForwardIndex() {
	// TODO Auto-generated destructor stub
}

void ForwardIndex::setup(size_t offset, string fInxUrl){
	// TODO initialization
	this->offset = offset;
	this->fInxUrl = fInxUrl;
	this->ifs.open(this->fInxUrl.c_str(), std::ios::in);
}

std::set<size_t> ForwardIndex::getUniqueTermId(size_t docId){
	// TODO get unique term id given the id of document
	set<size_t> rtr;

	//skip to line storing doc forward index
	string line="";
	for (size_t i=this->offset; i<=docId; ++i){
		getline(this->ifs, line);
	}
	ifs.seekg(0, std::ios::beg); //rewind the stream pointer

	//use regex to extract all termIds
	regex expr_termId(",\\d*,");
	sregex_iterator itMatch(line.begin(), line.end(), expr_termId);
	// empty iterator yields the end of the matching sequence
	sregex_iterator itMatchEnd;
	for(; itMatch!=itMatchEnd; ++itMatch){
		stringstream oss;
		oss << *itMatch;
		string termIdStr = oss.str().substr(1,oss.str().length()-2);
		size_t termId = (size_t) atoi(termIdStr.c_str());
		rtr.insert(termId);
	}
	return rtr;
}
