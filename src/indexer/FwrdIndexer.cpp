/*
 * FwrdIndexer.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: suz
 */

#include "FwrdIndexer.h"

FwrdIndexer::FwrdIndexer(){
	// TODO dummy dummy
}

FwrdIndexer::FwrdIndexer(string outputFolder){
	this->init(outputFolder);
}

void FwrdIndexer::init(string folder) {
	string outputpath = folder + "/ForwardIndex.txt";
	ofs.open(outputpath.c_str(),ios::out);
}

FwrdIndexer::~FwrdIndexer() {
	// TODO Auto-generated destructor stub
	ofs.close();
}

void FwrdIndexer::writeFwrdIndex(size_t docId, vector<size_t> termFreq, vector<size_t> termId, vector<int> termSrc){
	// TODO write forward index to the output stream
	string content=fUtil.getStringValue(docId) + " ";
	for (size_t i=0; i<termId.size(); i++){
		content += fUtil.getStringValue(termFreq.at(i)) +","+ fUtil.getStringValue(termId.at(i)) +","+ fUtil.getStringValue(termSrc.at(i)) + "|";
	}
	content += '\n';
	cout << content << endl;
	ofs<<content;

}

void FwrdIndexer::closeFile(){
	ofs.close();
}

