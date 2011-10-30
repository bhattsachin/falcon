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
#include <fstream>
#include <sstream>
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

	size_t queryTermId(const string term, bool& existFlag){
		Dictionary* dic = getTermDictionary();
		size_t termId = -1;
		if(dic->term.find(term) == dic->term.end()){
			existFlag = false;
			return termId;
		} else {

			dic->count[term]++;
			existFlag = true;
			return termId = dic->entry[term];
		}
	}

	void loadDictionary(string filepath);

};

#endif /* DICTIONARYUTIL_H_ */
