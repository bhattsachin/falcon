/*
 * DictionaryUtil.h
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 *
 */

#ifndef DICTIONARYUTIL_H_
#define DICTIONARYUTIL_H_

#include "Library.h"
#include "IDGenerator.h"

using namespace std;

class DictionaryUtil {

private:
	IDGenerator idGen;

public: struct Dictionary{
	set<string> term;
	map<string,size_t> entry;
	map<string, size_t> count;

};

public:
	DictionaryUtil();
	virtual ~DictionaryUtil();
	Dictionary* getTermDictionary(){
			//should have only one instance for this whole project. make it static
			static Dictionary termDictionary;
			return &termDictionary;
		}

	/**
	 * Returns termId for given term
	 */
	size_t getTermDictionaryTermId(const string term){
		Dictionary* dic = getTermDictionary();
		size_t termId;
		if(dic->term.find(term)==dic->term.end()){
			dic->term.insert(term);
			termId = idGen.getTermId();
			dic->entry[term] = termId;
			dic->count[term] = 1;
		}else{
			termId = dic->entry[term];
			dic->count[term]++;
		}
		return termId;
	}

	void loadDictionary(string filePath){

	}


};

#endif /* DICTIONARYUTIL_H_ */
