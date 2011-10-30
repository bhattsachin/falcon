/*
 * BinaryRetrieval.h
 *
 *  Created on: Oct 30, 2011
 *      Author: bhatt
 */

#ifndef BINARYRETRIEVAL_H_
#define BINARYRETRIEVAL_H_

#include "../utilities/Library.h"

using namespace std;

class BinaryRetrieval {
public:
	BinaryRetrieval();
	virtual ~BinaryRetrieval();
	list<size_t> search(vector<list<size_t> > postings);
};

#endif /* BINARYRETRIEVAL_H_ */
