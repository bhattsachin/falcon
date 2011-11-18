/*
 * BoostWikiParser.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: bhatt
 */

#include "BoostWikiParser.h"

BoostWikiParser::BoostWikiParser() {
	// TODO Auto-generated constructor stub

}

BoostWikiParser::~BoostWikiParser() {
	// TODO Auto-generated destructor stub
}

vector<string> BoostWikiParser::parseFile(string path) {
	FileUtil util;
	string inputText = util.readFile(path);

	//expression for a tag <<txt>>
	regex expr("(<)(<)((?:[A-Za-z][A-Za-z0-9_]*))(>)(>)");

	//expression for section ==txt==
	regex expr_section("(=)(=).*?(=)(=)");

	//expression for html tags ==txt==
	regex expr_html("(<[^>]+>)");

	//anything inside cbraces {{ }}
	regex expr_cbrace("(\\{.*?\\})");

	regex expr_sbrace("(\\[.*?\\])");

	regex expr_ccomment("(\\/\\*[\\d\\D]*?\\*\\/)");

	regex expr_unwantedChar("(\\}|\\]|;|,|'|:|\"|\\.|\\*|>|&nbsp)");

	string replacement = " ";
	// cout<<tstString<<endl;
	string replaced = regex_replace(inputText, expr, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_section, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_html, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_cbrace, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_sbrace, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_ccomment, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;
	replaced = regex_replace(replaced, expr_unwantedChar, replacement,
			boost::match_default | boost::format_sed);
	//cout << replaced << endl;

	return parse(replaced);


}
