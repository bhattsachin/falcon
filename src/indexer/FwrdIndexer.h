/*
 * FwrdIndexer.h
 *
 *  Created on: Oct 29, 2011
 *      Author: suz
 */

#ifndef FWRDINDEXER_H_
#define FWRDINDEXER_H_

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "../utilities/FileUtil.h"

using namespace std;

class FwrdIndexer {
private:
	FileUtil fUtil;
	ofstream ofs;
public:
	FwrdIndexer();
	FwrdIndexer(string outputFolder);
	virtual void init (string outputFolder);
	virtual ~FwrdIndexer();
	virtual void writeFwrdIndex(size_t, vector<size_t>, vector<size_t>, vector<int>);
	virtual void closeFile();
};

#endif /* FWRDINDEXER_H_ */
