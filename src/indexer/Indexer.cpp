/*
 * Indexer.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#include "Indexer.h"
#include "../utilities/FileUtil.h"

Indexer::Indexer() {


}

Indexer::~Indexer() {
	// TODO Auto-generated destructor stub
}

void Indexer::flush(Index* index){
	util.writeIndex(index);
	index->currentPostingCount = 0;
	index->flushCounter++;
	index->termIds.clear();
	index->postingList.clear();

}

void Indexer::buildIndex(Index* index, string fileId, size_t termId){
	//TODO: get this value from config file
	if(index->currentPostingCount>50000000){
		flush(index);
	}

	index->addPosting(fileId, termId);
}
