/*
 * ScoreBase.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#include "ScoreBase.h"

ScoreBase::ScoreBase(){
	// TODO dummy constructor
}

ScoreBase::~ScoreBase() {
	// TODO Auto-generated destructor stub
}

float ScoreBase::getScore(){
	// TODO return score
	return ScoreBase::staticScore;
}

void ScoreBase::setFileId(BoostParser::ParsedDocument* pdoc, vector<size_t>* termId, vector<int>* parts, size_t fileId){
	// TODO set the file Id, fetch info according to the Id
	this->pdoc = pdoc;
	this->termId = termId;
	this->parts = parts;
	this->fileId = fileId;

	this->refCount = this->pdoc->refCounter; // cov from size_t to int
	this->sectCount = this->pdoc->sections.size(); // cov from size_t to int
	for(size_t i=0; i < this->termId->size(); i++){
		if (parts->at(i) == 7){ // if part id shows that it's a category.
			this->categoryList.insert(termId->at(i));
		} else if(parts->at(i) == 4 || parts->at(i) == 5 || parts->at(i) == 6) { // if else, other content that is
			this->contentList.insert(termId->at(i));
		}
	}
}

int ScoreBase::getNumRefer(){
	//TODO get the number of reference
	return this->refCount;
}

int ScoreBase::getNumSection(){
	//TODO get the number of reference
	return this->sectCount;
}

set<size_t> ScoreBase::getWikiBody(){
	// TODO get the wiki body content (except category), term frequence will be ignored
	return this->contentList;
}

set<size_t> ScoreBase::getCatList(){
	//TODO get the category list(as their id in 'Category dictionary') of a wiki file.
	return this->categoryList;
}

