/*
 * FileHandler.cpp
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#include "FileHandler.h"
#include "../../utilities/FileUtil.h"
#include "../DocumentQueue.h"
#include "../../utilities/IDGenerator.h"
#include <iostream>

using namespace std;

FileHandler::FileHandler() {
	// TODO Auto-generated constructor stub

}

FileHandler::~FileHandler() {
	// TODO Auto-generated destructor stub
}

void FileHandler::read(std::string source) {

	vector<std::string> list;
	FileUtil util;
	list = util.getAllFileList(source, list);
	//read all the files


	unsigned long i = 0;
	while (i < list.size()) {

		queue.addToQueue(idGenerator.getDocId(), findDocumentType(list.at(i)),
				list.at(i));

		cout << list.at(i++) << endl;

	}

	//create a map of docId::vector string

}

/**
 * Finds document type based on path
 * data/DOC_TYPE/some/other/path
 *
 * extract DOC_TYPE
 */
std::string FileHandler::findDocumentType(std::string path) {

	size_t found;
	size_t second_occurence;
	std::string type;

	// different member versions of find in the same order as above:
	found = path.find("news");
	if (found != string::npos) {
		type="news";
	}else{
		found = path.find("wiki");
		if (found != string::npos)
				type="wiki";
	}

	return type;

}

