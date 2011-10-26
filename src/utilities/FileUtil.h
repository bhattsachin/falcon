/*
 * FileUtil.h
 * File handling operations
 *
 * work - sachin
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include "Library.h"
#include "../extraction/DocumentQueue.h"
#include "../indexer/Index.h"
#include "DictionaryUtil.h"

using namespace std;

class FileUtil {
public:
	FileUtil();
	string INDEX_FOLDER;

	virtual ~FileUtil();
	/**
	 * Returns total number of files to be processed.
	 * Only for display purpose.
	 * Remove if you think it's an overhead
	 */
	int getTotalFilesCount(std::string filePath, int count);
	/**
	 * Returns list with all file names to be processed from input filepath
	 */
	vector<std::string> getAllFileList(std::string filePath, vector<std::string> fileList);

	std::string readFile(std::string filePath);
	bool writeFile(const char* filename, std::string text);
	vector<size_t> writeDictionary(const char* filename, set<string> dictionary);
	bool writeIndex(Index* index);
	bool writeDictionary(const char* filename, vector<DocumentQueue::Document> *dictionary);
	bool writeDictionary(const char* filename, vector<DocumentQueue::FrequencyDictionary> dictionary);
	string findDocumentName(string path);
	string getStringValue(unsigned int value);
	bool writeDictionary(const char* filename, DictionaryUtil::Dictionary* dictionary);
	bool writeTermDictionary(const char* filename, DictionaryUtil::Dictionary* dictionary);
	bool createFolder(const char* foldername);
	string getFileNameFromPath(string path);


};

#endif /* FILEUTIL_H_ */
