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
#include "../indexer/Index.h"
#include <map>
#include <set>
#include <list>

using namespace std;
using namespace boost;
class InvertedIndex {

	map<string, map<size_t, list<Index::DocIdPairTF> > > invertedIndexMap;
	DictionaryUtil dictionary;



public:
	InvertedIndex();
	virtual ~InvertedIndex();
	void load();
	map<size_t,list<Index::DocIdPairTF> > getInvertedIndex(string query);
	list<Index::DocIdPairTF> getPostingList(string query);
	size_t getTF(string term, size_t docid);
};

#endif /* INVERTEDINDEX_H_ */
