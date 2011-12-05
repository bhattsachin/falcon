/*
 * ScoreWriter.cpp
 *
 *  Created on: Nov 26, 2011
 *      Author: suz
 */

#include "ScoreWriter.h"

ScoreWriter::ScoreWriter(){
	// TODO empty constructor stub
}

ScoreWriter::ScoreWriter(string outputFile) {
	// TODO Auto-generated constructor stub
	this->init(outputFile);
}

ScoreWriter::~ScoreWriter() {
	// TODO Auto-generated destructor stub
}

void ScoreWriter::init(string outputFile){
	ofs.open(outputFile.c_str(),ios::out);
}

void ScoreWriter::closeFile(){
	ofs.close();
}

void ScoreWriter::writeScoreFile(size_t docId, float score){
	string content=fUtil.getStringValue(docId) + " " + fUtil.getStringValue(score) + "\n";
	ofs<<content;
}
