/*
 * FileHandler.h
 * Reads/writes & handles file operations
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "../Crawler.h"
#include "../DocumentQueue.h"
#include "../../utilities/IDGenerator.h"

using namespace std;

class FileHandler : public Crawler {

	DocumentQueue queue;
	IDGenerator idGenerator;

public:
	FileHandler();
	virtual ~FileHandler();
	void read(std::string source);
	std::string findDocumentType(std::string path);

};

#endif /* FILEHANDLER_H_ */
