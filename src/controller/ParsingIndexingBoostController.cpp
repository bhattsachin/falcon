/*
 * ParsingIndexingBoostController.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: bhatt
 */

#include "ParsingIndexingBoostController.h"

ParsingIndexingBoostController::ParsingIndexingBoostController() {
	//TODO: remove this hard coding
	parser_map["news"] = new BoostParser();
	parser_map["wiki"] = new BoostWikiParser();
	parser_map["wiki"]->init("config/stopwords.txt");
	parser_map["news"]->init("config/stopwords.txt");

	/**
	 * FIXME: remove hard coding & get all values from config file
	 */
	//a-f
	barrel_map["000"] = new Index("000");
	//g-k
	barrel_map["001"] = new Index("001");
	//l-p
	barrel_map["002"] = new Index("002");
	//q-v
	barrel_map["003"] = new Index("003");
	//w-z
	barrel_map["004"] = new Index("004");

}

ParsingIndexingBoostController::~ParsingIndexingBoostController() {
	// TODO Auto-generated destructor stub
}

string ParsingIndexingBoostController::getBarrel(string word) {

	char startC = word[0];

	if (startC >= 97 && startC <= 102) {//a-f
		return "000";
	}
	if (startC >= 103 && startC <= 107) {//g-k
		return "001";
	}
	if (startC >= 108 && startC <= 112) {//l-p
		return "002";
	}
	if (startC >= 113 && startC <= 118) {//q-v
		return "003";
	}
	if (startC >= 119 && startC <= 122) {//w-z
		return "004";
	}

	return "004";

}

bool ParsingIndexingBoostController::configureEngine(string baseDir) {

	//read configuration file
	ConfigFile config("config/settings.config");
	//language type for this running instance
	std::string language;
	config.readInto(language, "lang");
	//extraction mechanism for this engine
	std::string reader;
	config.readInto(reader, "reader");
	//folder to read files from
	std::string folder;
	//config.readInto(folder, "file_read_dir");
	//cout << "input folder: " << folder;

	/**
	 * creating the instances
	 * Ideally crawler should be initialized
	 * based on type of reader from config file
	 * TODO: to be done as minor release
	 */

	crawler.read(baseDir);
	createOutputFolders();

	// added by Su, to initialize the forward indexer
	string outputFolder = "OUTPUT/fwd_index";
	fwrdindexer.init(outputFolder);

	/**
	 * once file are read
	 * parse them one by one
	 */
	DocumentQueue docqueue;
	vector<DocumentQueue::Document>* queue = docqueue.getQueue();

	//write file dictionary
	string name = "OUTPUT/dictionary/FileDictionary.txt";
	util.writeDictionary(name.c_str(), queue);

	cout << "@@@@@@ queue size:" << queue->size() << endl;

	DocumentQueue::Document doc;

	//vector containing all file content
	vector<string> tokenLst;

	vector<vector<string> > token_vector;
	for (int j = 0; j < (int) queue->size(); j++) {
		doc = queue->at(j);

		//get the parser
		tokenLst = parseFile(doc);

		indexFile(doc.id, tokenLst);
		//token_vector.push_back(tokenLst);
		cout << "--tokens inside:" << doc.path << " size:" << tokenLst.size()
				<< endl;

	}
	fwrdindexer.closeFile();
	//flush all the barrels
	map<string, Index*>::iterator mapItr;
	for (mapItr = barrel_map.begin(); mapItr != barrel_map.end(); mapItr++) {
		indexer.flush((*mapItr).second);
	}
	/**
	 * merge all vectors in one set
	 */

	set<string> unique_tokens;
	//temp store
	vector<string> inner_vector;
	token_vector.begin();
	for (int k = 0; k < (int) token_vector.size(); k++) {
		inner_vector = token_vector.at(k);
		for (int p = 0; p < (int) inner_vector.size(); p++) {
			unique_tokens.insert(inner_vector.at(p));
		}
	}

	cout << "# unique terms:" << dictUtil.getTermDictionary()->term.size()
			<< endl;

	//create term dictionary using termid & write to filesystem
	//iterate & add all text to a file using termid
	//TODO: remove this hard coding later
	name = "OUTPUT/dictionary/TermDictionary.txt";

	util.writeDictionary(name.c_str(), dictUtil.getTermDictionary());

	name = "OUTPUT/dictionary/TermCountDictionary.txt";
	util.writeTermDictionary(name.c_str(), dictUtil.getTermDictionary());
	name = "OUTPUT/dictionary/AuthorDictionary.txt";
	util.writeAuthorDictionary(name.c_str(), dictUtil.getAuthorDictionary());
	name = "OUTPUT/dictionary/CatDictionary.txt";
	util.writeCatDictionary(name.c_str(), dictUtil.getCatDictionary());
	/**
	 * create a term frequency counter dictionary
	 * expensive block :(
	 */

	//createTermCounterDictionary(unique_tokens, token_vector, termDictionary);


	return true;
}

map<string, size_t> ParsingIndexingBoostController::countFrequency(
		vector<string> lst) {
	map<string, size_t> count;

	for (size_t m = 0; m < lst.size(); m++) {
		if (count.find(lst.at(m)) != count.end()) {
			count.find(lst.at(m))->second = count.find(lst.at(m))->second + 1;

		} else {
			count.insert(pair<string, size_t> (lst.at(m), 1));
		}
	}

	return count;

}

void ParsingIndexingBoostController::indexFile(size_t fileId,
		vector<string> terms) {

	Index* barrel;
	string word;
	size_t term;
	vector<size_t> termIds;
	string val;
	map<string, size_t> count = countFrequency(terms);
	map<string, size_t>::iterator iter;

	for (iter = count.begin(); iter != count.end(); iter++) {
		val = "";
		word = iter->first;
		barrel = barrel_map[getBarrel(word)];
		term = dictUtil.getTermDictionaryTermId(word);
		termIds.push_back(term);
		val.append(util.getStringValue(fileId));
		val.append(",");
		val.append(util.getStringValue(count[word]));
		indexer.buildIndex(barrel, val, term);
	}

}

vector<string> ParsingIndexingBoostController::parseFile(
		DocumentQueue::Document doc) {
	BoostParser* parser;
	BoostParser::ParsedDocument pdoc;
	string semwikitext;
	vector<string> tmp;
	string filename;
	parser = parser_map[doc.type];
	pdoc = parser->parseFile(doc.path);
	tmp = pdoc.tokens;
	/**
	 * if this is wiki document create semwiki file
	 */
	if (doc.type.compare("wiki") == 0) {
		createSemWikiFiles(pdoc, doc.id);
	}

	return tmp;
}

void ParsingIndexingBoostController::createOutputFolders() {
	string folderOutput = "OUTPUT";
	util.createFolder(folderOutput.c_str());
	string folderName = "OUTPUT/SemWiki";
	util.createFolder(folderName.c_str());
	folderName = "OUTPUT/fwd_index";
	util.createFolder(folderName.c_str());
	folderName = "OUTPUT/inv_index";
	util.createFolder(folderName.c_str());
	folderName = "OUTPUT/dictionary";
	util.createFolder(folderName.c_str());
}

void ParsingIndexingBoostController::createSemWikiFiles(
		BoostParser::ParsedDocument doc, size_t docId) {

	vector<string> fwrdIndexTerms;
	vector<int> fwrdIndexParts;

	string semwikitext;
	string linkDictionary;
	string authorPairDictionary;
	string filename;
	string arti_name = doc.articleName.substr(
			doc.articleName.find_last_of("/\\") + 1);
	semwikitext += "<#ARTICAL NAME>\n" + arti_name + "\n";
	vector<string> arti_namev;
	arti_namev.push_back(arti_name);
	fwrdIndexTerms.insert(fwrdIndexTerms.end(),arti_namev.begin(),arti_namev.end());
	fwrdIndexParts.push_back(1);
	semwikitext += "<#AUTHOR>\n" + doc.author + "\n";
	size_t authorId = dictUtil.getAuthorDictionaryAuthorId(doc.author);
	vector<string> authorv;
	authorv.push_back(doc.author);
	fwrdIndexTerms.insert(fwrdIndexTerms.end(),authorv.begin(),authorv.end());
	fwrdIndexParts.push_back(2);
	semwikitext += "<#TIMESTAMP>\n" + doc.timestamp + "\n";
	vector<string> timestampv;
	timestampv.push_back(doc.timestamp);
	fwrdIndexTerms.insert(fwrdIndexTerms.end(),timestampv.begin(),timestampv.end());
	fwrdIndexParts.push_back(3);
	semwikitext += "<#INFOBOX>\n";
	BOOST_FOREACH(string t, doc.infobox)
				{
					semwikitext += t + "$";
				}

	fwrdIndexTerms.insert(fwrdIndexTerms.end(),doc.infobox.begin(),doc.infobox.end());
	vector<int> infoboxId(doc.infobox.size(),4);
	fwrdIndexParts.insert(fwrdIndexParts.end(), infoboxId.begin(),infoboxId.end());
	semwikitext += "\n<#SECTIONS>\n";

	BOOST_FOREACH(vector<string> subsec, doc.sections)
				{
					fwrdIndexTerms.insert(fwrdIndexTerms.end(),subsec.begin(),subsec.end());
					vector<int> sectionId(subsec.size(),5);
					fwrdIndexParts.insert(fwrdIndexParts.end(), sectionId.begin(),sectionId.end());
					BOOST_FOREACH(string t, subsec)
								{
									semwikitext += t + " ";
								}
					semwikitext += "\n";

				}

	semwikitext += "\n<#LINKS>\n";
	BOOST_FOREACH(string t, doc.links)
				{
					semwikitext += t + "\n";
					linkDictionary += util.removeExtension(arti_name) + " , " + t + "\n";
				}
	fwrdIndexTerms.insert(fwrdIndexTerms.end(), doc.links.begin(), doc.links.end());
	vector<int> InternLinkId(doc.links.size(),6);
	fwrdIndexParts.insert(fwrdIndexParts.end(), InternLinkId.begin(),InternLinkId.end());

	semwikitext += "\n<#CATEGORY>\n";
	BOOST_FOREACH(string t, doc.category)
				{
					semwikitext += t + "\n";
				}
	fwrdIndexTerms.insert(fwrdIndexTerms.end(), doc.category.begin(), doc.category.end());
	vector<int> wikiCatId(doc.category.size(),7);
	fwrdIndexParts.insert(fwrdIndexParts.end(), wikiCatId.begin(),wikiCatId.end());
	// write to forward index
	//	added: Zhiliang Su, Oct292011
	writeFwrdIndex(docId, fwrdIndexTerms, fwrdIndexParts);

	// write to semwiki file
	filename = (string) "OUTPUT/SemWiki/" + util.getFileNameFromPath(
			doc.articleName) + (string) " _semwiki_meta.txt";
	util.writeFile(filename.c_str(), semwikitext);

	//write author pair dictionary
	authorPairDictionary = util.removeExtension(arti_name) + " , " + doc.author + "\n";
	string authorPairFileName = "OUTPUT/dictionary/AuthorPairRepository.txt";
	util.writeFile(authorPairFileName.c_str(),authorPairDictionary);


	//write Link Repository
	string linkFileName = "OUTPUT/dictionary/LinkPairRepository.txt";
	util.writeFile(linkFileName.c_str(),linkDictionary);

}

void ParsingIndexingBoostController::writeFwrdIndex(size_t docId,
		vector<string> terms, vector<int> parts) {
	// TODO private function to write forward index
	vector<size_t> termId;
	vector<string>::iterator itTerms;

	// get term IDs
	for (size_t i = 0; i < terms.size(); i++) {
		// moded: Oct31, 2011 by Su
		//termId.push_back(dictUtil.getTermDictionaryTermId(*itTerms));
		switch (parts.at(i)) {
		case 1://Article name
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		case 2://Author name
			termId.push_back(dictUtil.getAuthorDictionaryAuthorId(terms.at(i)));
			break;
		case 3://Time stamp
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		case 4://Infobox
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		case 5://section
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		case 6://links
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		case 7://Category
			termId.push_back(dictUtil.getTermDictionaryTermId(terms.at(i)));
			break;
		}
	}

	// compute term frequency
	vector<size_t> termFreq;
	vector<size_t>::iterator itTermIda;
	vector<size_t>::iterator itTermIdb;
	for (itTermIda = termId.begin(); itTermIda != termId.end(); itTermIda++) {
		size_t tempCount = 0;
		for (itTermIdb = termId.begin(); itTermIdb != termId.end(); itTermIdb++) {
			if (*itTermIda == *itTermIdb) {
				tempCount++;
			}
		}
		termFreq.push_back(tempCount);
	}

	// use FwrdIndexer to write to file.(FwrdIndexer should maintain the barrel informations too, which we don't care now)
	fwrdindexer.writeFwrdIndex(docId, termFreq, termId, parts);
}

