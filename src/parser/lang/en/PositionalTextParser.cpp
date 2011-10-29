/*
 * PositionalTextParser.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: bhatt
 */

#include "PositionalTextParser.h"

PositionalTextParser::PositionalTextParser() {
	// TODO Auto-generated constructor stub

}

PositionalTextParser::~PositionalTextParser() {
	// TODO Auto-generated destructor stub
}

vector<PositionalTextParser::PositionalWord> PositionalTextParser::parse(string filepath){
	FileUtil util;
	string inputText = util.readFile(filepath);
	string deli = " ";
	vector<string> token;

	const string& inputToken = inputText;
	const string& delimitar = deli;
	vector<string>& outputToken = token;
	wordSplit(inputToken, delimitar, outputToken);

}

void PositionalTextParser::wordSplit(const string& str, const string& delim, vector<string>& parts) {
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


