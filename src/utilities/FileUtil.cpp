/*
 * FileUtil.cpp
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#include "FileUtil.h"
#include "Library.h"
#include "IDGenerator.h"

FileUtil::FileUtil() {
	INDEX_FOLDER = "index/";

}

FileUtil::~FileUtil() {
	// TODO Auto-generated destructor stub
}

int FileUtil::getTotalFilesCount(std::string basePath, int count) {
	std::string file_resource_path;
	DIR *dirp;
	struct dirent *dp;
	struct stat buf;

	dirp = opendir(basePath.c_str());
	if (!dirp) {
		cout << "Dirp is null" << endl;
		return false;
	}
	string file_resource_name;
	while ((dp = readdir(dirp))) {
		file_resource_name = dp->d_name;

		file_resource_path = basePath + '/' + file_resource_name;

		if ((file_resource_name == ".") || (file_resource_name == "..")
				|| (file_resource_name == "CVS"))
			continue;

		if (stat(file_resource_path.c_str(), &buf) == 0) {
			// recursively process directories
			if (buf.st_mode & S_IFDIR)
				count = getTotalFilesCount(file_resource_path, count);
			else
				count++;
		}
	}
	closedir(dirp);
	return count;
}

vector<std::string> FileUtil::getAllFileList(std::string basePath,
		vector<std::string> fileList) {
	std::string file_resource_path;
	DIR *dirp;
	struct dirent *dp;
	struct stat buf;

	dirp = opendir(basePath.c_str());
	if (!dirp) {
		cout << "Directory is null" << endl;
		return fileList;
	}
	string file_resource_name;
	while ((dp = readdir(dirp))) {
		file_resource_name = dp->d_name;

		file_resource_path = basePath + '/' + file_resource_name;

		if ((file_resource_name == ".") || (file_resource_name == "..")
				|| (file_resource_name == "CVS"))
			continue;

		if (stat(file_resource_path.c_str(), &buf) == 0) {
			// recursively process directories
			if (buf.st_mode & S_IFDIR)
				fileList = getAllFileList(file_resource_path, fileList);
			else
				fileList.push_back(file_resource_path);
		}
	}
	closedir(dirp);
	return fileList;
}

std::string FileUtil::readFile(std::string filePath) {
	string content = "";
	string line;
	ifstream ifs(filePath.c_str());
	if (ifs.is_open()) {
		while (!ifs.eof()) {
			getline(ifs, line);
			content += line;
		}
	} else {
		cout << "Couldn't open file " << filePath << endl;
	}

	//close the stream

	ifs.close();

	return content;
}

bool FileUtil::writeFile(const char* filename, std::string text) {
	ofstream file(filename);
	if (file.is_open()) {
		file << text;
		file.flush();
		file.close();
	} else {
		return false;
	}
	return true;
}

vector<size_t> FileUtil::writeDictionary(const char* filename,
		set<string> dictionary) {
	set<string>::iterator it;
	IDGenerator gen;
	size_t id;
	string output;
	vector<size_t> termDictionary;
	for (it = dictionary.begin(); it != dictionary.end(); it++) {
		id = gen.getTermId();
		output += "#" + getStringValue(id) + " " + *it + "\n";
		termDictionary.push_back(id);
	}

	writeFile(filename, output);
	return termDictionary;

}

bool FileUtil::writeDictionary(const char* filename,
		vector<DocumentQueue::Document> *dictionary) {
	set<string>::iterator it;
	IDGenerator gen;
	string output;
	DocumentQueue::Document doc;
	for (unsigned int i = 0; i < dictionary->size(); i++) {
		doc = dictionary->at(i);
		output += "#" + getStringValue(doc.id) + " " + findDocumentName(
				doc.path) + "\n";
	}

	return writeFile(filename, output);

}

string FileUtil::findDocumentName(string path) {
	size_t found;
	found = path.find_last_of("/\\");
	return path.substr(found + 1);
}

bool FileUtil::writeDictionary(const char* filename,
		vector<DocumentQueue::FrequencyDictionary> dictionary) {

	string output;
	DocumentQueue::FrequencyDictionary doc;
	for (unsigned int i = 0; i < dictionary.size(); i++) {
		doc = dictionary.at(i);
		output += "#" + getStringValue(doc.id) + " " + getStringValue(
				doc.frequency) + "\n";
	}
	return writeFile(filename, output);
}

string FileUtil::getStringValue(unsigned int value) {
	std::stringstream b;
	b << value;
	return b.str();

}

string FileUtil::getFileNameFromPath(string path){
	string name;
	unsigned int start = path.find_last_of("/");
	name = path.substr(start, path.length()-start);
	return name;
}

bool FileUtil::writeDictionary(const char* filename, DictionaryUtil::Dictionary* dictionary){
		string output;
		set<string>::iterator it;


		for (it = dictionary->term.begin(); it != dictionary->term.end(); it++) {
			output += getStringValue(dictionary->entry[*it]) + " " + *it + "\n";
		}
		return writeFile(filename, output);

}

bool FileUtil::writeTermDictionary(const char* filename, DictionaryUtil::Dictionary* dictionary){
		string output;
		set<string>::iterator it;


		for (it = dictionary->term.begin(); it != dictionary->term.end(); it++) {
			output += getStringValue(dictionary->entry[*it]) + " " + getStringValue(dictionary->count[*it]) + "\n";
		}
		return writeFile(filename, output);

}



bool FileUtil::writeIndex(Index* index) {
	string output;
	set<size_t>::iterator it,pit;
	set<size_t>* postingLst;
	set<size_t> terms = index->termIds;
	for (it = terms.begin(); it != terms.end(); it++) {
		postingLst = index->postingList[*it];
		output +=getStringValue(*it) + " ";
		bool firstItem = true;
		for (pit = postingLst->begin(); pit != postingLst->end(); pit++) {
			if(firstItem){
				output += getStringValue(*pit);
				firstItem = false;
			}else{
				output += "|" + getStringValue(*pit);
			}

		}
		//added for readability
		output +="\n";
	}
	string fileName;
	//cout<<"flush counter:"<<index->flushCounter<<endl;
	fileName ="inv_index/index.inv." + index->barrelId + "." + getStringValue(index->flushCounter);
	return writeFile(fileName.c_str(), output);


}

bool FileUtil::createFolder(const char* foldername){
	struct stat statBuf;
	if (stat(foldername, &statBuf) != 0) {
			mkdir(foldername, 0700);
		}

	return true;
}


/**

 int main() {
 FileUtil util;
 cout << "size:" << util.getTotalFilesCount("data", 0) << endl;

 vector<std::string> list;
 list = util.getAllFileList("data", list);
 //get all files
 cout << "file size:" << list.size() << endl;
 int i = 0;
 while (i < list.size()) {
 cout << list.at(i) << endl;
 cout << util.readFile(list.at(i++)) << endl;
 }

 util.writeFile("dummy","this is some text stuff");
 cout<<util.readFile("dummy");

 }

 */

