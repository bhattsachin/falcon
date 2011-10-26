/*
 * BaseParser.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */

#include "BaseParser.h"

BaseParser::BaseParser() {
}


void BaseParser::initParser(string stwFileUrl){
	stwListPath = stwFileUrl;
	if (stwList.size() == 0 || charExclude.size() == 0) {baseParserInit();}
}

BaseParser::~BaseParser() {
	flushMe();
	// TODO Auto-generated destructor stub
}

void BaseParser::baseParserInit(){
	//create stop word list
	ifstream* ifsPt = new ifstream();
	ifsPt->open(stwListPath.c_str(), ios::in);
	string currentTerm;
	while(*ifsPt >> currentTerm){
		stwList.push_back(currentTerm);
	}
	ifsPt->close();
	//char define not punctuation
	charExclude.push_back(45);
	for(int i=48; i<=57; i++){charExclude.push_back(i);}
	for(int i=65; i<=90; i++){charExclude.push_back(i);}
	for(int i=97; i<=122; i++){charExclude.push_back(i);}
}

void BaseParser::baseParseProc(vector<string> inputTerms){
	// TODO complete base parsing process

	for(int i=0; (unsigned int)i<inputTerms.size(); i++){
		inputTerms[i] = basePunc(inputTerms[i]);
		inputTerms[i] = baseHyphen(inputTerms[i]);
	}

	// merge
	semwiki.baseParsedTerms.insert(semwiki.baseParsedTerms.end(), inputTerms.begin(), inputTerms.end());
	semwiki.baseParsedTerms.insert(semwiki.baseParsedTerms.end(), addTerms.begin(), addTerms.end());
	// stop word removal
	baseSTW();
	// cases and numbers
	for(int i=0; (unsigned int)i<semwiki.baseParsedTerms.size(); i++){
		semwiki.baseParsedTerms[i] = baseCase(semwiki.baseParsedTerms[i]);
		semwiki.baseParsedTerms[i] = baseNum(semwiki.baseParsedTerms[i]);
	}

	//stemming proc
	for (int i=0; (unsigned int)i<semwiki.baseParsedTerms.size(); i++){
		semwiki.baseParsedTerms[i] = baseStem(semwiki.baseParsedTerms[i]);
	}

	//sort and unique
	sort(semwiki.baseParsedTerms.begin(), semwiki.baseParsedTerms.end());
	semwiki.baseParsedTerms.erase(unique(semwiki.baseParsedTerms.begin(), semwiki.baseParsedTerms.end()), semwiki.baseParsedTerms.end());

	//remove empty terms
	if (semwiki.baseParsedTerms[0] == ""){
		semwiki.baseParsedTerms.erase(semwiki.baseParsedTerms.begin());
	}

}

string BaseParser::baseCase(string inTerm){
	// TODO normalize all letter cases into lower-case
	for(unsigned int i=0; i<inTerm.length(); i++){
		if(inTerm[i]>=65 && inTerm[i]<=90){
			inTerm[i] = inTerm[i] + 32;
		}
	}
	return inTerm;
}

string BaseParser::baseNum(string inTerm){
	// TODO nothing
	return inTerm;
}

void BaseParser::baseSTW(){
	//TODO remove stop-words
	for(int i=0; (unsigned int)i < stwList.size(); i++){
		semwiki.baseParsedTerms.erase(remove( semwiki.baseParsedTerms.begin(),semwiki.baseParsedTerms.end() , stwList[i] ) ,semwiki.baseParsedTerms.end());
	}
}

string BaseParser::basePunc(string inTerm){
	// TODO remove punctuation characters
	vector<int>::iterator it;
	string separateItem="";
	/*
	for(int i=0; (unsigned int)i<inTerm.size(); i++){
		it = find(charExclude.begin(), charExclude.end(), (int)inTerm[i]);
		if (it == charExclude.end()){
				inTerm[i] = ' ';
		}
	}*/

	for (int i=0; (unsigned int)i<inTerm.size(); i++){
		if((inTerm[i]>=48&&inTerm[i]<=57)||(inTerm[i]>=65&&inTerm[i]<=90)||(inTerm[i]>=97&&inTerm[i]<=122)||(inTerm[i]==45)){
			//do nothing to word/num/hyphens
		}else{
			inTerm[i]=' ';
		}
	}

	string combStr = "";
	string delimar = " ";
	vector<string> token;
	const string& inputT = inTerm;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	for (int i=0; (unsigned int)i<token.size(); i++){
		combStr += token[i];
	}
	return combStr;
}

string BaseParser::baseHyphen(string inTerm){
	// TODO remove hyphens and return combined term and store divided terms into 'addTerms' vector
	string comStr = "";
	string delimar = "-";
	vector<string> token;
	const string& inputT = inTerm;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	addTerms.insert(addTerms.end(),token.begin(),token.end());
	for(unsigned int i=0 ; i<token.size(); i++){
		if (i==0){
			comStr += token[i];
		}else{
			comStr += deli + token[i];
		}
	}
	return comStr;
}

string BaseParser::baseStem(string inTerm){
	// TODO do nothing dummy foo...
	return inTerm;
}

void BaseParser::baseToolSplit(const string& str, const string& delim, vector<string>& parts) {
	size_t start, end = 0;
	while (end < str.size()) {
		start = end;
		while (start < str.size() && (delim.find(str[start]) != string::npos)) {
			start++;  // skip initial whitespace
		}
		end = start;
		while (end < str.size() && (delim.find(str[end]) == string::npos)) {
			end++; // skip to end of word
		}
		if (end-start != 0) {  // just ignore zero-length strings.
			parts.push_back(string(str, start, end-start));
		}
	}
}

void BaseParser::flushMe(){
	// TODO clean base parser variance
	semwiki.baseParsedTerms.clear();
	semwiki.baseParsedTerms.erase(semwiki.baseParsedTerms.begin(),semwiki.baseParsedTerms.end());
	addTerms.clear();
	addTerms.erase(addTerms.begin(),addTerms.end());
}

BaseParser::SemWiki BaseParser::parse(string filename){
	vector<string> vec;
	vec.push_back("foo");
	vec.push_back("bar");
	semwiki.baseParsedTerms = vec;
	return semwiki;
}

