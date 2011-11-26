/*
 * ScoreBase.h
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#ifndef SCOREBASE_H_
#define SCOREBASE_H_

#include "../../parser/BoostParser.h"

#include <string>
#include <fstream>
#include <math.h>	// for floor
//#include <boost/regex.hpp>
#include <sstream>
#include <vector>
//#include <boost/algorithm/string.hpp> // for split
#include <stdlib.h> // for atoi

using namespace std;
using namespace boost;
class ScoreBase {
public:
	ScoreBase();
	//ScoreBase(vector<ifstream*> ifsPtrList, size_t offset, size_t barrelSize);
	virtual ~ScoreBase();
	void setFileId(BoostParser::ParsedDocument* pdoc, vector<size_t>* termId, vector<int>* parts, size_t fileId);
	// getters
	virtual float getScore();
	int getNumSection();
	int getNumRefer();
	set<size_t> getCatList();
	set<size_t> getWikiBody();

protected:
	// private vars
	set<size_t> categoryList;
	set<size_t> contentList;
	int refCount;
	int sectCount;
	size_t fileId;
	float staticScore;

	BoostParser::ParsedDocument* pdoc;
	vector<size_t>* termId;
	vector<int>* parts;

};

#endif /* SCOREBASE_H_ */
