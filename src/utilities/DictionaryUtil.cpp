/*
 * DictionaryUtil.cpp
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#include "DictionaryUtil.h"

DictionaryUtil::DictionaryUtil() {
	// TODO Auto-generated constructor stub

}

DictionaryUtil::~DictionaryUtil() {
	// TODO txAuto-generated destructor stub
}

void DictionaryUtil::loadDictionary(string filepath){

	ifstream* ifspt = new ifstream(filepath.c_str());
	if(ifspt->is_open()){
		Dictionary* dic = getTermDictionary();
		string term;
		string termIdstr;
		size_t termId;
		while(*ifspt){
			*ifspt >> termIdstr >> term;
			std::istringstream iss(termIdstr);
			iss >> termId;
			dic->term.insert(term);
			dic->entry[term] = termId;
			dic->count[term] = 1;
		}
	}
}

void DictionaryUtil::loadDocDictionary(string filepath){
	ifstream* ifspt = new ifstream(filepath.c_str());
	if (ifspt->is_open()){
		vector<DocumentQueue::Document>* fileDic = getDocDictionary();

		size_t docId;
		string docIdstr;
		string docPath;
		string docType;
		while(*ifspt){
			DocumentQueue::Document* tempFileDic;
			*ifspt >> docIdstr >> docPath >> docType;
			std::istringstream iss(docIdstr);
			iss >> docId;
			tempFileDic->id=docId;
			tempFileDic->path=docPath;
			tempFileDic->type=docType;
			fileDic->push_back(*tempFileDic);
		}
	}
}

void DictionaryUtil::loadAuthorDictionary(string filepath){
	ifstream* ifspt = new ifstream(filepath.c_str());
	AuthorDictionary* dic = getAuthorDictionary();
	if (ifspt->is_open()){
		size_t authorId;
		string authorIdstr;
		string author;
		*ifspt>>authorIdstr >> author;
		std::istringstream iss(authorIdstr);
		iss >> authorId;
		dic->author.insert(author);
		dic->entry[author] = authorId;
	}
}

void DictionaryUtil::loadCatDictionary(string filepath){
	ifstream* ifspt = new ifstream(filepath.c_str());
	CatDictionary* dic = getCatDictionary();
	if (ifspt->is_open()){
		size_t catId;
		string catIdstr;
		string cat;
		*ifspt>> catIdstr >> cat;
		std::istringstream iss(catIdstr);
		iss >> catId;
		dic->cat.insert(cat);
		dic->entry[cat] = catId;
	}
}

/*
int main(){
	DictionaryUtil util;
	util.loadDictionary("OUTPUT/dictionary/TermDictionary.txt");
	string cmd;
	bool existFlag = false;
	bool& flagR = existFlag;
	size_t termId;
	while(cin>>cmd){
		flagR = false;
		termId = util.queryTermId(cmd, flagR);
		if (flagR){
			cout << "Term: "<< cmd << " with ID: " << termId << endl;
		} else {
			cout << "Term: " << cmd << " not found  :`(" << endl;
		}
	}

}
*/
