/*
 * ParsingController.h
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#ifndef PARSINGCONTROLLER_H_
#define PARSINGCONTROLLER_H_

#include "../utilities/Library.h"
#include "../extraction/fileio/FileHandler.h"
#include "../parser/BaseParser.h"
#include "../extraction/DocumentQueue.h"
#include "../utilities/FileUtil.h"

using namespace std;



class ParsingController {
	//holds parser information
	std::map<std::string, BaseParser*> parser_map;
	//handle to the crawler. file handler in this case
	FileHandler crawler;
	//handle to document queue - stores all records to process
	DocumentQueue task_queue;
	FileUtil util;
public:
	ParsingController();
	virtual ~ParsingController();
	bool configureEngine();
private:
	void createTermCounterDictionary(set<string> unique_tokens, vector<vector<string> > token_vector, vector<size_t> termDictionaryId );
};

#endif /* PARSINGCONTROLLER_H_ */
