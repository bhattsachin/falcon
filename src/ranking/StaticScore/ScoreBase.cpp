/*
 * ScoreBase.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#include "ScoreBase.h"

ScoreBase::ScoreBase(vector<ifstream*> ifsPtrList, size_t offset, size_t barrelSize) {
	// TODO Auto-generated constructor stub
	this->ifsPtrList = ifsPtrList;
	this->offset = offset;
	this->barrelSize = barrelSize;
}

ScoreBase::~ScoreBase() {
	// TODO Auto-generated destructor stub
}

float ScoreBase::getScore(){
	// TODO return score
	return ScoreBase::staticScore;
}

void ScoreBase::setFileId(size_t fileId){
	// TODO set the file Id and call several methods to retrieve reference/section count, content/category list and etc.
	this->fileId = fileId;
	this->refCount = 0;
	this->sectCount = 0;
	// use regular expression to parse a forward index string
    regex expr_refCount("\\[\\d+\\]");
    regex expr_tftidpartid("\\d+,\\d+,\\d+");
    sregex_iterator itMatchEnd;
    sregex_iterator itMatchRef(this->frwdIndxStream.begin(), this->frwdIndxStream.end(), expr_refCount);
    sregex_iterator itMatchBody(this->frwdIndxStream.begin(), this->frwdIndxStream.end(), expr_tftidpartid);

    // store results
    this->refCount = atoi(itMatchRef->str().c_str());
    vector<string> body;
    for(; itMatchBody!=itMatchEnd; ++itMatchBody){
    	body.push_back(itMatchBody->str());
		vector<string> tokens;
		boost::split(tokens, *it, boost::is_any_of(", |"),token_compress_on);
		if (tokens.at(2) == "7"){
			this->categoryList.push_back(str2sizet(tokens.at(1)));
		} else if(tokens.at(2) == "5"){
			this->sectCount++;
			this->contentList.push_back(str2sizet(tokens.at(1)));
		} else {
			this->contentList.push_back(str2sizet(tokens.at(1)));
		}
    }
}

void ScoreBase::fetchFwrdIndx(){
	// TODO fetch the forward index in forward index barrels according to the 'fileId' given and the offset kept in memory.
	size_t numBarrel = floor((fileId-offset)/barrelSize);
	size_t inFileOffset = fileId - (barrelSize * numBarrel);

	// get the forward index for fileId
	for (size_t i = 0; i < inFileOffset; i++){
		*ifsPtrList.at(numBarrel) >> ScoreBase::frwdIndxStream;
	}

	// set the stream get pointer to the beginning of the buffer
	ifsPtrList.at(numBarrel)->seekg(0, ios::beg);
}

int ScoreBase::getNumRefer(){
	//TODO get the number of reference
	return this->refCount;
}

int ScoreBase::getNumSection(){
	//TODO get the number of reference
	return this->sectCount;
}

vector<size_t> ScoreBase::getWikiBody(){
	// TODO get the wiki body content (except category), term frequence will be ignored
	return this->contentList;
}

vector<size_t> ScoreBase::getCatList(vector<string> body){
	//TODO get the category list(as their id in 'Category dictionary') of a wiki file.
	return this->categoryList;
}

size_t ScoreBase::str2sizet(string input){
	// TODO helper for converting string to size_t value
	size_t rtr;
	std::istringstream iss(input);
	iss >> rtr;
	return rtr;
}
