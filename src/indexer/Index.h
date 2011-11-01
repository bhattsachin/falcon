/*
 * Index.h
 * Represents an Index document barrel
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "../utilities/Library.h"


using namespace std;

class Index {

public:
	Index(string barrelId);
	virtual ~Index();

	//each Index file has a barrel id
	string barrelId;
	//counts how many times this file has been flushed
	size_t flushCounter;
	size_t currentPostingCount;
	set<size_t> termIds;
	map<size_t, set<string>* > postingList;

	void addToIndex(size_t termId);
	//all the terms present in given docId for given barrel
	void addPosting(string docId, size_t termId);
	//flush everything to file, clear termId & postingList & currentPostingCount & increment flushCounter
	void flush();



};

#endif /* INDEX_H_ */
