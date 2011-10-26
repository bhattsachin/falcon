/*
 * Index.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#include "Index.h"

Index::Index(string mBarrelId) {
	barrelId = mBarrelId;
	flushCounter = 0;

}

Index::~Index() {
	// TODO Auto-generated destructor stub
}


void Index::addPosting(size_t docId, size_t termId){
	addToIndex(termId);
	set<size_t>* postingL = postingList[termId];
	postingL->insert(docId);
	//cout<<"##termId:"<<termId<<" docId:"<<docId;
	currentPostingCount++;
}

void Index::addToIndex(size_t termId){
	//add to this termId set
	if(termIds.find(termId)==termIds.end()){
		termIds.insert(termId);

		postingList[termId] = new set<size_t>();
	}


}

/**
 * Write to output file once exceeds limits or asked for
 */
void Index::flush(){
	//util.writeIndex(this);

}
