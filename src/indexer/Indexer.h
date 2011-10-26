/*
 * Indexer.h
 *
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include "Index.h"
#include "../utilities/FileUtil.h"

class Indexer {
	FileUtil util;
public:
	Indexer();
	virtual ~Indexer();
	void flush(Index* index);
	void buildIndex(Index* index, size_t fileId, size_t termId);
	//TODO: fix this hardcoding
	//std::map<std::string, BaseParser*> parser_map;
};

#endif /* INDEXER_H_ */
