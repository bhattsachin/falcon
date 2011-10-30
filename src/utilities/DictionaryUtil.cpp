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

/**
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
