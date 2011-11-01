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
#include "../extraction/DocumentQueue.h"
#include <fstream>
#include <sstream>
using namespace std;

class DictionaryUtil {

private:
	IDGenerator idGen;
	ifstream* ifsptAuthor;
public:

	struct Dictionary{
		set<string> term;
		map<string,size_t> entry;
		map<string, size_t> count;

	};

	struct AuthorDictionary{
		set<string> author;
		map<string, size_t> entry;
	};

	struct CatDictionary{
		set<string> cat;
		map<string, size_t> entry;
	};

	DictionaryUtil();
	virtual ~DictionaryUtil();
	Dictionary* getTermDictionary(){
		//should have only one instance for this whole project. make it static
		static Dictionary termDictionary;
		return &termDictionary;
	}
	vector<DocumentQueue::Document>* getDocDictionary(){
		static vector<DocumentQueue::Document> docDictionary;
		return &docDictionary;
	}
	AuthorDictionary* getAuthorDictionary(){
		static AuthorDictionary authorDictionary;
		return &authorDictionary;
	}
	CatDictionary* getCatDictionary(){
		static CatDictionary catDictionary;
		return &catDictionary;
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

	size_t getAuthorDictionaryAuthorId(const string author){
		AuthorDictionary* authorDic = getAuthorDictionary();
		size_t authorId;
		if(authorDic->author.find(author)==authorDic->author.end()){
			authorDic->author.insert(author);
			authorId = idGen.getAuthorId();
			authorDic->entry[author] = authorId;
		}else{
			authorId = authorDic->entry[author];
		}
		return authorId;
	}

	size_t getCatDictionaryCatId(const string cat){
		CatDictionary* catDic = getCatDictionary();
		size_t catId;
		if(catDic->cat.find(cat)==catDic->cat.end()){
			catDic->cat.insert(cat);
			catId = idGen.getCatId();
			catDic->entry[cat] = catId;
		} else {
			catId = catDic->entry[cat];
		}
		return catId;
	}

	size_t queryCatId(const string cat, bool& existFlag){
		CatDictionary* catDic = getCatDictionary();
		size_t catId=-1;
		if(catDic->cat.find(cat)==catDic->cat.end()){
			existFlag = false;
			return catId;
		} else {
			existFlag = true;
			return catId = catDic->entry[cat];
		}
	}

	size_t queryAuthorId(const string author, bool& existFlag){
		AuthorDictionary* authorDic = getAuthorDictionary();
		size_t authorId=-1;
		if(authorDic->author.find(author)==authorDic->author.end()){
			existFlag=false;
			return authorId;
		}else{
			existFlag = true;
			return authorId = authorDic->entry[author];
		}
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
	void loadDocDictionary(string filepath);
	void loadAuthorDictionary(string filepath);
	void loadCatDictionary(string filepath);
};

#endif /* DICTIONARYUTIL_H_ */
