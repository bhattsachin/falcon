/*
 * IDGenerator.h
 *
 *  Created on: Sep 13, 2011
 *      Author: bhatt
 *
 *	work: Zhilliang
 *      Creates unique static id's for documents
 *
 */



#ifndef IDGENERATOR_H_
#define IDGENERATOR_H_

#include "Library.h"

using namespace std;

class IDGenerator {

public:

	IDGenerator();
	virtual ~IDGenerator();
	size_t getDocId(){
		static size_t docId = 0;
		docId++;
		return docId;
	}

	size_t getTermId(){
		static size_t termId = 0;
		termId++;
		return termId;
	}
};



#endif /* IDGENERATOR_H_ */
