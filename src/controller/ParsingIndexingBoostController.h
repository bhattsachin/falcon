/*
 * ParsingIndexingBoostController.h
 *
 *  Created on: Nov 17, 2011
 *      Author: bhatt
 */

#ifndef PARSINGINDEXINGBOOSTCONTROLLER_H_
#define PARSINGINDEXINGBOOSTCONTROLLER_H_

#include "../utilities/Library.h"
#include "../extraction/fileio/FileHandler.h"
#include "../parser/BoostParser.h"
#include "../parser/BoostWikiParser.h"
#include "../extraction/DocumentQueue.h"
#include "../utilities/FileUtil.h"
#include "../utilities/DictionaryUtil.h"
#include "../indexer/Index.h"
#include "../indexer/Indexer.h"
#include "../indexer/FwrdIndexer.h"
#include "../utilities/ConfigFile.h"

using namespace std;

class ParsingIndexingBoostController {
	//holds parser information
	std::map<std::string, BoostParser*> parser_map;
	//handle to the crawler. file handler in this case
	FileHandler crawler;
	//handle to document queue - stores all records to process
	DocumentQueue task_queue;
	FileUtil util;
	DictionaryUtil dictUtil;
	Indexer indexer;
	FwrdIndexer fwrdindexer;
	map<string, Index*> barrel_map;

public:
	ParsingIndexingBoostController();
	bool configureEngine(string baseDir);
	string getBarrel(string word);
	void indexFile(size_t fileId, vector<string> terms);
	vector<string> parseFile(DocumentQueue::Document doc);
	void parseWiki(string path);
	virtual ~ParsingIndexingBoostController();

private:
	void createOutputFolders();
	void writeFwrdIndex(size_t, vector<string> , vector<int> );
	map<string, size_t> countFrequency(vector<string> lst);

};

#endif /* PARSINGINDEXINGBOOSTCONTROLLER_H_ */
