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
#include <boost/regex.hpp>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp> // for split
#include <stdlib.h> // for atoi

using namespace std;
using namespace boost;
class ScoreBase {
public:
	ScoreBase(BoostParser::ParsedDocument pdoc);
	ScoreBase(vector<ifstream*> ifsPtrList, size_t offset, size_t barrelSize);
	virtual ~ScoreBase();
	void setFileId(size_t fileId);
	// getters
	virtual float getScore();
	int getNumSection();
	int getNumRefer();
	vector<size_t> getCatList();
	vector<size_t> getWikiBody();

protected:
	// private vars
	vector<ifstream*> ifsPtrList;
	size_t offset;
	size_t barrelSize;

	vector<size_t> categoryList;
	vector<size_t> contentList;
	int refCount;
	int sectCount;
	size_t fileId;
	float staticScore;
	string frwdIndxStream;

	BoostParser::ParsedDocument pdoc;

	// helpers
	void fetchFwrdIndx();
	size_t str2sizet(string);
};

#endif /* SCOREBASE_H_ */
