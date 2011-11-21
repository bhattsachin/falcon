/*
 * BoostParser.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: bhatt
 */

#include "BoostParser.h"

BoostParser::BoostParser() {
	// TODO Auto-generated constructor stub

}

BoostParser::~BoostParser() {
	// TODO Auto-generated destructor stub
}

void BoostParser::init(string stopWordsFile){
		//create stop word list
		//you might want to ad error handling if file not found
		ifstream* ifsPt = new ifstream();
		ifsPt->open(stopWordsFile.c_str(), ios::in);
		string currentTerm;
		while(*ifsPt >> currentTerm){
			stop_words.push_back(currentTerm);
		}
		ifsPt->close();

}

BoostParser::ParsedDocument BoostParser::parseFile(string path) {
	FileUtil util;
	BoostParser::ParsedDocument doc;
	string inputText = util.readFile(path);
	doc.tokens = parse(inputText);
	return doc;

}


vector<string> BoostParser::parse(string text) {
	list<string> tmp;
	vector<string> tokens;
	list<string> tokenList;
	split(tokenList, text, is_any_of("."), token_compress_on);
	BOOST_FOREACH(string t, tokenList)
				{
					split(tmp, t, is_any_of(" ,\t;':-()"), token_compress_on);
					BOOST_FOREACH(string t, tmp)
								{
									t = trim_left_copy(t);
									t = trim_right_copy(t);
									algorithm::to_lower(t);
									if (t.length() > 1) {
										//if stop word ignore
										tokens.push_back(t);
									}
								}
				}

	return tokens;

}
