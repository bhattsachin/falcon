/*
 * ParsingController.cpp
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#include "ParsingController.h"
#include "../utilities/ConfigFile.h"
#include "../extraction/fileio/FileHandler.h"
#include "../parser/BaseParser.h"
#include "../parser/lang/en/PlainTextParser.h"
#include "../parser/lang/en/WikiParser.h"


#include <iterator>

using namespace std;

ParsingController::ParsingController() {

	//TODO: remove this hard coding
	parser_map["wiki"] = new WikiParser();
	parser_map["news"] = new PlainTextParser();

}

ParsingController::~ParsingController() {
	// TODO Auto-generated destructor stub
}

bool ParsingController::configureEngine() {


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
	config.readInto(folder, "file_read_dir");
	cout << "input folder: " << folder;
	/**
	 * creating the instances
	 * Ideally crawler should be initialized
	 * based on type of reader from config file
	 * TODO: to be done as minor release
	 */

	crawler.read(folder);

	/**
	 * once file are read
	 * parse them one by one
	 */
	DocumentQueue docqueue;
	vector<DocumentQueue::Document>* queue = docqueue.getQueue();

	//write file dictionary
	string name = "FileDictionary.txt";
	util.writeDictionary(name.c_str(), queue);

	cout << "@@@@@@ queue size:" << queue->size() << endl;

	DocumentQueue::Document doc;
	BaseParser* parser;

	//vector containing all file content
	vector<string> tmp;
	vector<vector<string> > token_vector;
	for (int j = 0; j < (int) queue->size(); j++) {
		doc = queue->at(j);

		//get the parser
		parser = parser_map[doc.type];
		parser->initParser("config/stopwords.txt");
		tmp = parser->parse(doc.path).baseParsedTerms;
		token_vector.push_back(tmp);
		cout << "^^^^^^^^^ tokens inside:" << doc.path << " size:"
				<< token_vector.at(j).size() << endl;
	}

	cout << "total vector size:" << token_vector.size() << endl;

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

	cout << "# unique terms:" << unique_tokens.size() << endl;

	//create term dictionary using termid & write to filesystem
	//iterate & add all text to a file using termid
	//TODO: remove this hard coding later
	name = "TermDictionary.txt";

	vector<size_t> termDictionary;
	termDictionary = util.writeDictionary(name.c_str(), unique_tokens);

	/**
	 * create a term frequency counter dictionary
	 * expensive block :(
	 */

	createTermCounterDictionary(unique_tokens, token_vector, termDictionary);

	cout << "lang:" << language << " reader:" << reader << " folder:" << folder
			<< endl;

	return true;
}

void ParsingController::createTermCounterDictionary(set<string> unique_tokens,
		vector<vector<string> > token_vector, vector<size_t> termDictionaryId) {
	unsigned int counter;
	vector<string> inner_vector;
	vector<DocumentQueue::FrequencyDictionary> freq_dictionary;
	DocumentQueue::FrequencyDictionary term;
	set<string>::iterator it;
	vector<int> termCounter;
	unsigned int cnt=0;
	for (it = unique_tokens.begin(); it != unique_tokens.end(); it++) {
		counter = 0;
		for (int k = 0; k < (int) token_vector.size(); k++) {
			inner_vector = token_vector.at(k);

			for (int p = 0; p < (int) inner_vector.size(); p++) {
				if (inner_vector.at(p).compare(*it) == 0) {
					counter++;
				}
			}
		}
		term.frequency=counter;
		term.id = termDictionaryId.at(cnt++);
		freq_dictionary.push_back(term);
		cout << *it << " " << counter << endl;
		termCounter.push_back(counter);
	}

	//write to dictionary
	string freq_dict_name = "FrequencyDictionary";
	util.writeDictionary(freq_dict_name.c_str(), freq_dictionary);

}

