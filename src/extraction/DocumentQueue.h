/*
 * DocumentQueue.h
 *
 *  Created on: Sep 20, 2011
 *      Author: bhatt
 */

#ifndef DOCUMENTQUEUE_H_
#define DOCUMENTQUEUE_H_

#include "../utilities/Library.h"

using namespace std;

class DocumentQueue {

	//FIXME: make this struct use char instead of string to save space

	public:struct Document {
	public:
		size_t id;    // 10 char code for the document id.
		string type;   // 3-char code for the document type. wiki/news/web
		string  path;        // path of the file
		};

	public:struct FrequencyDictionary {
		public:
			size_t id;
			unsigned int frequency;
	};



public:
	DocumentQueue();
	virtual ~DocumentQueue();
	void addToQueue(size_t id, string type, string path);
	vector<Document>* getQueue(){
		//should have only one instance for this whole project. make it static
		static vector<Document> documentQueue;
		return &documentQueue;
	}


};

#endif /* DOCUMENTQUEUE_H_ */
