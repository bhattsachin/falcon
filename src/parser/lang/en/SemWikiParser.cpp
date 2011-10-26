/*
 * SemWikiParser.cpp
 *
 *  Created on: Oct 2, 2011
 *      Author: Zhiliang SU
 */

#include "SemWikiParser.h"
#include "../../../utilities/FileUtil.h"

SemWikiParser::SemWikiParser() {
	// TODO Auto-generated constructor stub

}

SemWikiParser::~SemWikiParser() {
	// TODO Auto-generated destructor stub
}

vector<SemWikiParser::swParsedTerm> SemWikiParser::parse(string filepath){
	//TODO main sem wiki file parse proc
	swParsedTerm swPT;
	// read file split each word into token vector;
	FileUtil util;
	string inputText = util.readFile(filepath);
	string delimar = " ";
	vector<string> token;
	const string& inputT = inputText;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	// find type
	for (unsigned int i=0; i<token.size(); i++){
		if(findType(token[i])!=0){
			if(procCode==1){
				swParsedTerm swptTemp;
				swptTemp.swTerm = token[i];
				swptTemp.swType = typeCode;
				swTerms.push_back(swptTemp);
			}else if(procCode==2 || findType(token[i])==3){
				vector<string> tempSeptToken;
				string delimar = "$";
				vector<string>& tempSeptTokenR = tempSeptToken;
				const string& inputR = token[i];
				const string& deliR = delimar;
				baseToolSplit(inputR, deliR, tempSeptTokenR);
				for(unsigned int j=0; j<tempSeptToken.size(); j++){
					tempSeptToken[j] = baseHyphen(tempSeptToken[j]);
					if(procCode==3){// punc removal for the third type of meta infos
						swParsedTerm swptTemp;
						swptTemp.swTerm = basePunc(tempSeptToken[j]);
						swptTemp.swType = typeCode;
						if (swptTemp.swTerm!=""){swTerms.push_back(swptTemp);}
					}else{
						swParsedTerm swptTemp;
						swptTemp.swTerm = tempSeptToken[j];
						swptTemp.swType = typeCode;
						if (swptTemp.swTerm!=""){swTerms.push_back(swptTemp);}
					}
				}
			}
		}
	}
	// return
	return swTerms;
}

string SemWikiParser::basePunc(string inputTx){
	// TODO remove punctuation characters
	for (int i=0; (unsigned int)i<inputTx.size(); i++){
		if((inputTx[i]>=48&&inputTx[i]<=57)||(inputTx[i]>=65&&inputTx[i]<=90)||(inputTx[i]>=97&&inputTx[i]<=122)||(inputTx[i]==45)){
			//do nothing to word/num/hyphens
		}else{
			inputTx[i]=' ';
		}
	}

	string combStr = "";
	string delimar = " ";
	vector<string> token;
	const string& inputT = inputTx;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	for (int i=0; (unsigned int)i<token.size(); i++){
		combStr += token[i];
	}
	return combStr;
}

string SemWikiParser::baseHyphen(string inTerm){
	// TODO remove hyphens and return combined term and store divided terms into 'addTerms' vector
	string comStr = "";
	string delimar = "-";
	vector<string> token;
	const string& inputT = inTerm;
	const string& deli = delimar;
	vector<string>& outputT = token;
	baseToolSplit(inputT, deli, outputT);
	for(unsigned int i=0 ; i<token.size(); i++){
		if (i==0){
			comStr += token[i];
		}else{
			comStr += deli + token[i];
		}
	}
	return comStr;
}

int SemWikiParser::findType(string inputTx){
	//  procCode: 0,1,2,3 means:
	//		1. single string value don't need any further operatons on it;
	//		2. multiple lines string vector value but don't need punc removal;
	//		3. multiple lines string vector need punc removal;
	//		0. type title meant to be skipped.
	if(inputTx=="<#ARTICAL NAME>"){typeCode = 1; procCode=1; return 0;}
	if(inputTx=="<#AUTHOR>"){typeCode = 2; procCode=1; return 0;}
	if(inputTx=="<#TIMESTAMP>"){typeCode = 3; procCode=1; return 0;}
	if(inputTx=="<#INFOBOX>"){typeCode = 4; procCode=3; return 0;}
	if(inputTx=="<#TAXOBOX>"){typeCode = 5;procCode=3; return 0;}
	if(inputTx=="<#SECTIONS>"){typeCode = 6;procCode=2; return 0;}
	if(inputTx=="<#LINKS>"){typeCode = 7;procCode=2; return 0;}
	if(inputTx=="<#CATEGORY>"){typeCode = 8;procCode=2; return 0;}
	else{
		return procCode;
	}
}

void SemWikiParser::baseToolSplit(const string& str, const string& delim, vector<string>& parts) {
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
