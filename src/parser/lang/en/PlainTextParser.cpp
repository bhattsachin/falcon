/*
 * PlainTextParser.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */


#include "PlainTextParser.h"
#include "../../../utilities/FileUtil.h"


PlainTextParser::PlainTextParser() {
	// TODO Auto-generated constructor stub
}

PlainTextParser::~PlainTextParser() {
	// TODO Auto-generated destructor stub
}

void PlainTextParser::plainParseProcIpt(ifstream* ifsPt){
	// TODO main white space parser process for a file stream input
	//erase the whole vector
	plainRawTerms.erase(plainRawTerms.begin(),plainRawTerms.end());
	string currentTerm;
	while(*ifsPt >> currentTerm){
		plainRawTerms.push_back(currentTerm);
	}
	PlainTextParser::baseParseProc(plainRawTerms);
}

vector<string> PlainTextParser::plainParseProcStr(string inputText){

	// TODO white space parser process for a string input
	//erase the whole vector
	//this->plainRawTerms.erase(plainRawTerms.begin(),plainRawTerms.end());
	string delimar = " ";
	vector<string> token;
	const string& inputT = inputText;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	plainRawTerms = token;
	baseParseProc(this->plainRawTerms);

	return semwiki.baseParsedTerms;
}

BaseParser::SemWiki PlainTextParser::parse(string filepath){

	FileUtil util;
	string inputText = util.readFile(filepath);
	semwiki.baseParsedTerms = plainParseProcStr(inputText);
	return semwiki;
}

void PlainTextParser::flushMe(){
	// TODO clean plain text parser variance
	plainRawTerms.clear();
	plainRawTerms.erase(plainRawTerms.begin(),plainRawTerms.end());
	semwiki.baseParsedTerms.clear();
	semwiki.baseParsedTerms.erase(semwiki.baseParsedTerms.begin(),semwiki.baseParsedTerms.end());
	addTerms.clear();
	addTerms.erase(addTerms.begin(),addTerms.end());
}

