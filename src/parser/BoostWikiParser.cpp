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

BoostParser::ParsedDocument BoostWikiParser::parseFile(string path) {
	FileUtil util;
	BoostParser::ParsedDocument doc;
	string inputText = util.readFile(path);

	doc.articleName = path;

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



	//parsing content

	string::const_iterator start, end;
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default;

	//fetch author
	regex expr_author("(<<Author>>:)(.*?)(<<)");
	start = inputText.begin();
	end = inputText.end();
	boost::regex_search(start, end, what, expr_author, flags);
	doc.author = what[2];

	//timestamp

	regex expr_timestamp("(<<Timestamp>>:)(.*?)(<<)");
	start = inputText.begin();
	end = inputText.end();
	regex_search(start, end, what, expr_timestamp, flags);
	doc.timestamp = what[2];

	//infobox

	regex expr_infobox("(\\{\\{Infobox)(.*?)(\\}\\})");
	start = inputText.begin();
	end = inputText.end();
	regex_search(start, end, what, expr_infobox, flags);
	string infobox = what[2];
	regex expr_metaInfo("(\\|).*?(=\\s+)");
	//Removing meta characters
	infobox = regex_replace(infobox, expr_metaInfo, replacement,
			boost::match_default | boost::format_sed);
	doc.infobox = parse(infobox);

	/**
	 * This block smells. inspect it
	 */

	//sections
	regex expr_wikisection(
			"(==)(.*?)(==)(\\s+)((?:[A-Za-z0-9][a-zA-Z0-9]+))(.*?)(==)");
	start = inputText.begin();
	end = inputText.end();
	vector<vector<string> > section;
	while (boost::regex_search(start, end, what, expr_wikisection, flags)) {
		section.push_back(parse(what[2] + " " + what[5]));
		start = what[5].second;
	}
	doc.sections = section;

	//links internal
	string txt;
	regex expr_links("(\\[\\[)((?:[A-Za-z0-9()\\s+:'][A-Za-z0-9()\\s+:']+))");
	regex expr_space("(\\s+)");
	start = inputText.begin();
	end = inputText.end();
	while (boost::regex_search(start, end, what, expr_links, flags)) {
		txt = what[2];
		txt = regex_replace(txt, expr_space, "_",
					boost::match_default | boost::format_sed);
		doc.links.push_back(txt);
		cout<<"txt is:"<<txt<<endl;

		start = what[0].second;
	}


	//reference counter
	doc.refCounter = 0;
	regex expr_ref("(<ref\\s+)");
	start = inputText.begin();
	end = inputText.end();
	while (boost::regex_search(start, end, what, expr_ref, flags)) {
		doc.refCounter++;
		start = what[0].second;
	}

	//external links: uncomment if required

	/**
		regex expr_http("(http:\\/.*?)(((?:\\/[\\w\\.\\-]+)+))");
		start = inputText.begin();
		end = inputText.end();
		while (boost::regex_search(start, end, what, expr_http, flags)) {
			doc.links.push_back(what[1] + what[2]);
			start = what[0].second;
		}

	 */

	//fetch category

	regex expr_category("(\\[\\[Category:)(.*?)(\\]\\])");
	start = inputText.begin();
	end = inputText.end();
	while (boost::regex_search(start, end, what, expr_category, flags)) {
		doc.category.push_back(what[2]);
		start = what[0].second;
	}


	//content parsing over

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


	doc.tokens = parse(replaced);

	return doc;

}
