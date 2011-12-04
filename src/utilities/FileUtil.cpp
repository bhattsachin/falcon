/*
 * FileUtil.cpp
 *
 *  Created on: Sep 14, 2011
 *      Author: bhatt
 */

#include "FileUtil.h"
#include "Library.h"
#include "IDGenerator.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

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
	ofstream file(filename,ios_base::app);
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

string FileUtil::getStringValue(size_t value) {
	std::stringstream b;
	b << value;
	return b.str();
}

string FileUtil::getStringValue(int value) {
	std::stringstream b;
	b << value;
	return b.str();
}

string FileUtil::getStringValue(float value) {
	std::stringstream b;
	b << value;
	return b.str();
}

string FileUtil::getFileNameFromPath(string path) {
	string name;
	unsigned int start = path.find_last_of("/");
	name = path.substr(start, path.length() - start);
	return name;
}

bool FileUtil::writeDictionary(const char* filename,
		DictionaryUtil::Dictionary* dictionary) {
	string output;
	set<string>::iterator it;

	for (it = dictionary->term.begin(); it != dictionary->term.end(); it++) {
		output += getStringValue(dictionary->entry[*it]) + " " + *it + "\n";
	}
	return writeFile(filename, output);

}

bool FileUtil::writeTermDictionary(const char* filename,
		DictionaryUtil::Dictionary* dictionary) {
	string output;
	set<string>::iterator it;

	for (it = dictionary->term.begin(); it != dictionary->term.end(); it++) {
		output += getStringValue(dictionary->entry[*it]) + " "
				+ getStringValue(dictionary->count[*it]) + "\n";
	}
	return writeFile(filename, output);

}

bool FileUtil::writeIndex(Index* index) {
	string output;
	set<size_t>::iterator it;
	set<string>::iterator pit;
	set<string>* postingLst;
	set<size_t> terms = index->termIds;
	for (it = terms.begin(); it != terms.end(); it++) {
		postingLst = index->postingList[*it];
		output += getStringValue(*it) + " ";
		bool firstItem = true;
		for (pit = postingLst->begin(); pit != postingLst->end(); pit++) {
			if (firstItem) {
				output += *pit;
				firstItem = false;
			} else {
				output += "|" + *pit;
			}

		}
		//added for readability
		output += "\n";
	}
	string fileName;
	//cout<<"flush counter:"<<index->flushCounter<<endl;
	fileName = "OUTPUT/inv_index/index.inv." + index->barrelId + "."
			+ getStringValue(index->flushCounter);
	return writeFile(fileName.c_str(), output);

}

bool FileUtil::createFolder(const char* foldername) {
	struct stat statBuf;
	if (stat(foldername, &statBuf) != 0) {
		mkdir(foldername, 0700);
	}

	return true;
}
/**
 * Reads inverted index of the form termid<space><docid1>|<docid2>|<docid3>......<docidn>
 */
map<size_t, list<Index::DocIdPairTF> > FileUtil::readNonPositionalInvertedIndex(
		string filepath) {
	string content = "";
	size_t termId;
	string posting;
	list<Index::DocIdPairTF> postinglist;
	map<size_t, list<Index::DocIdPairTF> > index;
	string line;
	ifstream ifs(filepath.c_str());
	if (ifs.is_open()) {
		while (ifs) {
			//cout << termId << " " << posting << endl;
			ifs >> termId >> posting;
			postinglist = getPostings(posting);
			index.insert(pair<size_t, list<Index::DocIdPairTF> > (termId, postinglist));

		}
	} else {
		cout << "Couldn't open file " << filepath << endl;
	}

	//close the stream
	ifs.close();

	return index;
}

map<size_t, list<Index::DocIdPairTF> > FileUtil::readInvertedIndex(
		string filepath) {
	string content = "";
	size_t termId;
	string posting;
	list<Index::DocIdPairTF> postinglist;
	map<size_t, list<Index::DocIdPairTF> > index;
	string line;
	ifstream ifs(filepath.c_str());
	if (ifs.is_open()) {
		while (ifs) {
			//cout << termId << " " << posting << endl;
			ifs >> termId >> posting;
			postinglist = getPostings(posting);
			index.insert(pair<size_t, list<Index::DocIdPairTF> > (termId, postinglist));

		}
	} else {
		cout << "Couldn't open file " << filepath << endl;
	}

	//close the stream
	ifs.close();

	return index;
}


list<size_t> &FileUtil::split(const string &s, char delim, list<size_t> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(atol(item.c_str()));
	}
	return elems;
}

list<size_t> FileUtil::split(const string &s, char delim) {
	list<size_t> elems;
	return split(s, delim, elems);
}

list<size_t> &FileUtil::splitToGetPosting(const string &s, char delim, list<size_t> &elems) {
	stringstream ss(s);
	string item;
	string temp;
	while (getline(ss, item, delim)) {
		temp = item.substr(0,item.find_first_of(','));
		elems.push_back(atol(temp.c_str()));
	}
	return elems;
}

list<size_t> FileUtil::splitToGetPosting(const string &s, char delim) {
	list<size_t> elems;
	return split(s, delim, elems);
}

list<Index::DocIdPairTF> FileUtil::getPostings(string s){
	list<Index::DocIdPairTF> postings;
	Index::DocIdPairTF item;
	list<string> docs;
	list<string> tf;
	boost::split(docs, s, is_any_of("|"), token_compress_on);
	BOOST_FOREACH(string t, docs){
		boost::split(tf, t, is_any_of(","), token_compress_on);
		item.docid = atoi(tf.front().c_str());
		item.tf = atoi(tf.back().c_str());
		postings.push_back(item);
	}

	return postings;


}

void FileUtil::mergeInvertedIndex(string pattern) {

	vector<string> indexList;
	//read all the files in the given folder
	indexList = getAllFileList("OUTPUT/inv_index", indexList);

	list<string> barrelList;

	for (int i = 0; i < indexList.size(); i++) {
		if (indexList.at(i).find(pattern) != string::npos) {
			barrelList.push_back(indexList.at(i));
		}
	}

	//cout << "size:" << indexList.size() << endl;

	//cout << "barrel size:" << barrelList.size() << endl;

	//write that one file //keep all files open
	vector<list<FileUtil::PostingEntry> > postingBuffer;
	FileUtil::PostingEntry posStruct;
	size_t termId;
	string posting;
	size_t counter = 0;
	while (!barrelList.empty()) {
		ifstream ifs(barrelList.front().c_str());
		list<FileUtil::PostingEntry> postingList;
		if (ifs.is_open()) {
			while (ifs) {
				//cout << termId << " " << posting << endl;
				ifs >> termId >> posting;
				posStruct.posting = posting;
				posStruct.termId = termId;
				postingList.push_back(posStruct);

			}
			postingBuffer.push_back(postingList);
			counter++;
		} else {
			cout << "Couldn't open file " << barrelList.front() << endl;
		}

		ifs.close();
		remove(barrelList.front().c_str());
		barrelList.pop_front();

	}

	size_t min;

	list<FileUtil::PostingEntry> finalPosting;

	FileUtil::PostingEntry entry;

	while (true) {

		min = 999999999;
		bool alive = false;

		for (size_t k = 0; k < postingBuffer.size(); k++) {
			list<FileUtil::PostingEntry> posEntry;
			posEntry = postingBuffer.at(k);

			if (posEntry.size() > 0 && posEntry.front().termId < min) {
				min = posEntry.front().termId;
				alive = true;
			}

		}

		//termination condition for this loop
		if (!alive)
			break;

		string posting;
		bool first = true;
		for (size_t k = 0; k < postingBuffer.size(); k++) {
			list<FileUtil::PostingEntry> posEntry;
			posEntry = postingBuffer.at(k);

			if (posEntry.size() > 0) {
				if (posEntry.front().termId == min) {
					if (first) {
						posting = posEntry.front().posting;
						posEntry.pop_front();
						postingBuffer.at(k) = posEntry;
						first = false;
					} else {
						posting.append("|");
						posting.append(posEntry.front().posting);
						posEntry.pop_front();
						postingBuffer.at(k) = posEntry;
					}
				}
			}

		}
		entry.termId = min;
		entry.posting = posting;
		finalPosting.push_back(entry);

		//cout << "termid" << entry.termId << "---entry:" << entry.posting
		//		<< endl;

	}

	string writeFileName = "OUTPUT/inv_index/";

	string text;
	writeFileName.append(pattern);

	while (!finalPosting.empty()) {
		text += getStringValue(finalPosting.front().termId);
		text += " ";
		text += finalPosting.front().posting;
		text += "\n";
		//file <<
		finalPosting.pop_front();

	}

	writeFile(writeFileName.c_str(), text);

}

bool FileUtil::writeAuthorDictionary(const char* filename, DictionaryUtil::AuthorDictionary* authorList){
	string output;
	set<string>::iterator it;
	for(it=authorList->author.begin(); it!=authorList->author.end(); it++){
		output += getStringValue(authorList->entry[*it]) + " " + *it + '\n';
	}
	return writeFile(filename, output);
}

bool FileUtil::writeCatDictionary(const char* filename, DictionaryUtil::CatDictionary* catList){
	string output;
	set<string>::iterator it;
	for(it=catList->cat.begin(); it!=catList->cat.end(); it++){
		output += getStringValue(catList->entry[*it]) + " " + "*it" + "\n";
	}
	return writeFile(filename, output);
}

string FileUtil::removeExtension(string filename){
	size_t dot = filename.find_first_of(".");
	if(dot!=string::npos)
		filename = filename.substr(0,dot);
	return filename;
}


/**
 * for spliting posting lists
 */

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


/**

int main() {

	FileUtil util;
	map<size_t, list<size_t> > index;
	string filepath = "OUTPUT/inv_index/index.inv.000.1";
	index = util.readNonPositionalInvertedIndex(filepath);
	list<size_t> posting;

	map<size_t, list<size_t> >::iterator iter;
	for (iter = index.begin(); iter != index.end(); iter++) {
		cout << "#termid " << iter->first << " - ";
		posting = iter->second;
		while (!posting.empty()) {
			cout << posting.front() << "|";
			posting.pop_front();
		}
		cout << endl;

	}

	cout << "we are done" << endl;


	//remove("OUTPUT/inv_index/index.inv.000.1");
}

*/


