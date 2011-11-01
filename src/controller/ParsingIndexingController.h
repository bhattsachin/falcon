/*
 * ParsingIndexingController.h
 *
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#ifndef PARSINGINDEXINGCONTROLLER_H_
#define PARSINGINDEXINGCONTROLLER_H_

#include "../utilities/Library.h"
#include "../extraction/fileio/FileHandler.h"
#include "../parser/BaseParser.h"
#include "../extraction/DocumentQueue.h"
#include "../utilities/FileUtil.h"
#include "../utilities/DictionaryUtil.h"
#include "../indexer/Index.h"
#include "../indexer/Indexer.h"
#include "../indexer/FwrdIndexer.h"
#include "../parser/lang/en/WikiParser.h"
#include "WikiController.h"

using namespace std;

class ParsingIndexingController {
	//holds parser information
		std::map<std::string, BaseParser*> parser_map;
		//handle to the crawler. file handler in this case
		FileHandler crawler;
		//handle to document queue - stores all records to process
		DocumentQueue task_queue;
		FileUtil util;
		DictionaryUtil dictUtil;
		Indexer indexer;
		FwrdIndexer fwrdindexer;
		WikiParser* semWikiParser;
		map<string, Index*> barrel_map;

	public:
		ParsingIndexingController();
		virtual ~ParsingIndexingController();
		bool configureEngine(string baseDir);
		string getBarrel(string word);
		void indexFile(size_t fileId, vector<string> terms);
		vector<string> parseFile(DocumentQueue::Document doc);
		void parseWiki(string path);
	private:
		void createOutputFolders();
		void writeFwrdIndex(size_t, vector<string>, vector<int>);
		map<string,size_t> countFrequency(vector<string> lst);

	};

#endif /* PARSINGINDEXINGCONTROLLER_H_ */
