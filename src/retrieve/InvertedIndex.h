/*
 * InvertedIndex.h
 *
 *  Created on: Oct 29, 2011
 *      Author: bhatt
 *      Fetches posting from inverted index files into memory
 */

#ifndef INVERTEDINDEX_H_
#define INVERTEDINDEX_H_

#include "../utilities/Library.h"
#include "../utilities/FileUtil.h"
#include "../utilities/DictionaryUtil.h"

using namespace std;
class InvertedIndex {

	map<string, map<size_t, list<size_t> > > invertedIndexMap;
	DictionaryUtil dictionary;

public:
	InvertedIndex();
	virtual ~InvertedIndex();
	void load();
	map<size_t,list<size_t> > getInvertedIndex(string query);
	list<size_t> getPostingList(string query);
};

#endif /* INVERTEDINDEX_H_ */
