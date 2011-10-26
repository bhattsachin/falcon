/*
 * WikiParser.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: Zhiliang SU
 */

#include "WikiParser.h"

WikiParser::WikiParser() {
	// TODO Auto-generated constructor stub

}

WikiParser::~WikiParser() {
	flushMe();
}

BaseParser::SemWiki WikiParser::parse(string filepath) {
	// TODO extract semantic metas from a wiki file line by line. also will
	//		extract terms from a wiki file.
	//term extraction proc
	string line;
	string content;
	ifstream ifs(filepath.c_str());
		if (ifs.is_open()) {
			while (!ifs.eof()) {
				getline(ifs, line);
				wikiExtractMeta(line);
				content += line;
			}
		} else {
			cout << "Couldn't open file " << filepath << endl;
		}

	ifs.close();
	plainParseProcStr(content);



	return semwiki;
}

void WikiParser::wikiExtractMeta(string lineTx) {
	// TODO extract semantic metas by using multiple methods from WikiParser
	if(!semWikiFlags.cat)
		wikiGetCat(lineTx);
	if(!semWikiFlags.artName)
	wikiGetArtName(lineTx);
	if(!semWikiFlags.author)
	wikiGetAuthor(lineTx);
	if(!semWikiFlags.timeStamp)
	wikiGetTimeStamp(lineTx);
	if(!semWikiFlags.internalLink)
	wikiGetInternLink(lineTx);


	if(!semWikiFlags.infoBox)
	wikiGetInfobox(lineTx);
	if(!semWikiFlags.taxoBox)
	wikiGetTaxobox(lineTx);
	wikiGetSection(lineTx);
}

void WikiParser::initParserWiki(string stwFileUrl) {
	WikiParser::initParser(stwFileUrl);
}

void WikiParser::wikiGetCat(string lineTx) {
	// TODO extract category infos from the input text.
	string tempCat;
	if (lineTx.find("[[Category:") != string::npos || lineTx.find(
			"[[:Category:") != string::npos) {
		if (lineTx.find("|") != string::npos) {
			tempCat = lineTx.substr(lineTx.find("Category:") + 9,
					lineTx.find("|") - lineTx.find("Category:") - 9);
			semwiki.wikiCategory.push_back(wikiToolReplace(tempCat, ' ', '_'));
		} else {
			semwiki.wikiCategory.push_back(
					lineTx.substr(lineTx.find("Category:") + 9,
							lineTx.find("]]") - lineTx.find("Category:") - 9));
		}
		semWikiFlags.cat = true;
	}
}

void WikiParser::wikiGetInfobox(string lineTx) {
	// TODO extract infobox from the input text.
	if (!infoHold && lineTx.find("{{Infobox") != string::npos) {
		// hold for dumping infobox contents
		infoHold = true;
		// get infobox name
		semwiki.wikiInfobox.push_back(
				lineTx.substr(lineTx.find("Infobox") + 8,
						lineTx.length() - lineTx.find("Infobox") - 8));
	}
	if (infoHold) {
		if (lineTx == "}}") {
			infoHold = false;
			semWikiFlags.infoBox = true;
		} else {
			semwiki.wikiInfobox.push_back(lineTx);

		}
	}

}

void WikiParser::wikiGetTaxobox(string lineTx) {
	// TODO extract taxobox from the input text.
	if (!taxoHold && lineTx.find("{{Taxobox") != string::npos) {
		// hold for dumping taxobox contents
		taxoHold = true;
	}
	if (taxoHold) {
		if (lineTx == "}}") {
			taxoHold = false;
			semWikiFlags.taxoBox = true;
		} else {
			semwiki.wikiTaxobox.push_back(lineTx);
		}
	}
}

void WikiParser::wikiGetArtName(string lineTx) {
	// TODO extract artical name from the input text.
}

void WikiParser::wikiGetAuthor(string lineTx) {
	// TODO extract author name from the input text.
	//cout<<lineTx<<endl;
	if (lineTx.find("<<Author>>:") != string::npos) {
		semwiki.wikiAuthor = lineTx.substr(lineTx.find("Author>>:") + 10,
				lineTx.length() - lineTx.find("Author>>:") - 10);
		semWikiFlags.author = true;
	}
}

void WikiParser::wikiGetTimeStamp(string lineTx) {
	// TODO extract timestamp from the input text.
	if (lineTx.find("<<Timestamp>>:") != string::npos) {
		semwiki.wikiTimeStamp = lineTx.substr(lineTx.find("Timestamp>>:") + 13,
				lineTx.length() - lineTx.find("Timestamp>>:") - 13);
		semWikiFlags.timeStamp = true;
	}
}

void WikiParser::wikiGetInternLink(string lineTx) {
	// TODO extract internal links from the input text.
	deque<int> contentPos;
	int pairCount = (int) contentPos.size() / 2;
	contentPos = wikiToolFindMkup(lineTx, "[[", "]]");
	for (int i = 0; i < pairCount; i++) {
		semwiki.wikiInternLink.push_back(
				lineTx.substr(contentPos[i], contentPos[i + pairCount]));
	}
}

void WikiParser::wikiGetSection(string lineTx) {
	// TODO extract setction infos from the input text.
	//cout<<lineTx<<endl;
	if ((int) lineTx.find("==") == 0) {
		sectHold = false;
		// erase a wikiSectPart vector
		if (!tempSection.empty()) {
			semwiki.wikiSection.push_back(tempSection);
			tempSection = "";
		}
	}
	if (!sectHold && (int) lineTx.find("==") == 0) {// section found
		sectHold = true;
		sectWordCount = 0;
		int sectDeep;
		sectDeep = (int) lineTx.find_first_not_of("=");
		// push section title.
		tempSection += lineTx.substr(sectDeep,
				(int) lineTx.length() - (2 * sectDeep));
		return;
	}
	if (sectHold) {
		WikiParser::plainParseProcStr(lineTx);
		if ((int) PlainTextParser::semwiki.baseParsedTerms.size() > 0) {
			for (int i = 0; (unsigned int) i
					< PlainTextParser::semwiki.baseParsedTerms.size(); i++) {
				tempSection += "$" + PlainTextParser::semwiki.baseParsedTerms[i];
				sectWordCount++;
				if (sectWordCount >= 20) {
					sectHold = false;
					break;
				}
			}
		}
	}
}

void WikiParser::flushMe() {

	plainRawTerms.clear();
	plainRawTerms.erase(plainRawTerms.begin(), plainRawTerms.end());
	semwiki.baseParsedTerms.clear();
	semwiki.baseParsedTerms.erase(semwiki.baseParsedTerms.begin(), semwiki.baseParsedTerms.end());
	addTerms.clear();
	addTerms.erase(addTerms.begin(), addTerms.end());
	// TODO clean wiki parser variance


	 tempSection.clear();
	 tempSection.erase(tempSection.begin(),tempSection.end());
	 semwiki.wikiInternLink.clear();
	 semwiki.wikiInternLink.erase(semwiki.wikiInternLink.begin(),semwiki.wikiInternLink.end());
	 semwiki.wikiCategory.clear();
	 semwiki.wikiCategory.erase(semwiki.wikiCategory.begin(),semwiki.wikiCategory.end());
	 semwiki.wikiInfobox.clear();
	 semwiki.wikiInfobox.erase(semwiki.wikiInfobox.begin(),semwiki.wikiInfobox.end());
	 semwiki.wikiTaxobox.clear();
	 semwiki.wikiTaxobox.erase(semwiki.wikiTaxobox.begin(),semwiki.wikiTaxobox.end());
	 semwiki.wikiSection.clear();
	 semwiki.wikiSection.erase(semwiki.wikiSection.begin(),semwiki.wikiSection.end());
	 semwiki.wikiArticalName.clear();
	 semwiki.wikiArticalName.erase(semwiki.wikiArticalName.begin(),semwiki.wikiArticalName.end());
	 semwiki.wikiAuthor.clear();
	 semwiki.wikiAuthor.erase(semwiki.wikiAuthor.begin(),semwiki.wikiAuthor.end());
	 semwiki.wikiTimeStamp.clear();
	 semwiki.wikiTimeStamp.erase(semwiki.wikiTimeStamp.begin(),semwiki.wikiTimeStamp.end());

	 semWikiFlags.artName = false;
	 semWikiFlags.author = false;
	 semWikiFlags.cat = false;
	 semWikiFlags.infoBox = false;
	 semWikiFlags.internalLink = false;
	 semWikiFlags.section = false;
	 semWikiFlags.taxoBox = false;
	 semWikiFlags.timeStamp = false;

}

string WikiParser::wikiToolReplace(string inputTx, char oriChar, char rpcChar) {
	// TODO replace oriChar with rpcChar in inputTx
	for (int i = 0; (unsigned int) i < inputTx.length(); i++) {
		if (inputTx[i] == oriChar) {//replace white space in category names with an underscore.
			inputTx[i] = rpcChar;
		}
	}
	return inputTx;
}

deque<int> WikiParser::wikiToolFindMkup(string inputTx, string mkBegin,
		string mkEnd) {
	// TODO find mark-up pairs in inputTx and push the start-pos and content length into a deque.
	//		the front part of the Deque contains starting-positions of the content, and the rear
	//		part contains the length of the content
	deque<int> contentPos;
	int posBegin;
	int posEnd;
	int lenMkBegin;

	lenMkBegin = (int) mkBegin.length();

	posBegin = (int) inputTx.find(mkBegin, 0);
	posEnd = (int) inputTx.find(mkEnd, 0);

	while (posBegin >= 0 && posEnd >= 0) {
		contentPos.push_front(posBegin + lenMkBegin);
		contentPos.push_back(posEnd - posBegin - lenMkBegin);
		posBegin = (int) inputTx.find(mkBegin, posBegin + 2);
		posEnd = (int) inputTx.find(mkEnd, posEnd + 2);
	}
	return contentPos;
}
