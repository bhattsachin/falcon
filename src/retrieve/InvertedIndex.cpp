/*
 * InvertedIndex.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: bhatt
 */

#include "InvertedIndex.h"

InvertedIndex::InvertedIndex() {
	// TODO Auto-generated constructor stub

}

InvertedIndex::~InvertedIndex() {
	// TODO Auto-generated destructor stub
}

void InvertedIndex::load(){
	FileUtil util;

	invertedIndexMap["000"] = util.readNonPositionalInvertedIndex("OUTPUT/inv_index/index.inv.000");
	invertedIndexMap["001"] = util.readNonPositionalInvertedIndex("OUTPUT/inv_index/index.inv.001");
	invertedIndexMap["002"] = util.readNonPositionalInvertedIndex("OUTPUT/inv_index/index.inv.002");
	invertedIndexMap["003"] = util.readNonPositionalInvertedIndex("OUTPUT/inv_index/index.inv.003");
	invertedIndexMap["004"] = util.readNonPositionalInvertedIndex("OUTPUT/inv_index/index.inv.004");

}

map<size_t,list<Index::DocIdPairTF> > InvertedIndex::getInvertedIndex(string query){
	char c = query.at(0);

	c = tolower(c);

	if(97<=c && c<=102){
		return invertedIndexMap["000"];
	}else if(103<=c && c<=107){
		return invertedIndexMap["001"];
	}else if(108<=c && c<=112){
		return invertedIndexMap["002"];
	}else if(113<=c && c<=117){
		return invertedIndexMap["003"];
	}else if(118<=c && c<=122){
		return invertedIndexMap["004"];
	}else{
		return invertedIndexMap["000"];
	}


}

list<Index::DocIdPairTF> InvertedIndex::getPostingList(string query){
	//cout<<"query input"<<query<<endl;
	map<size_t,list<Index::DocIdPairTF> > postingIndex = getInvertedIndex(query);

	size_t termId = dictionary.getTermDictionaryTermId(query);

	//postingIndex.

	list<Index::DocIdPairTF> postingList = postingIndex.at(termId); //(postingIndex.find(termId));

	//cout<<"size of posting list present for this term:"<<postingList.size()<<endl;

	return postingList;

}

size_t InvertedIndex::getTF(string term, size_t docid){
	list<Index::DocIdPairTF> postings = getPostingList(term);
	size_t tf=0;

	BOOST_FOREACH(Index::DocIdPairTF t, postings){
		if(t.docid==docid){
			tf = t.tf;
			break;
		}
	}

	return tf;
}


