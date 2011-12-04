/*
 * Cosine.h
 *
 *  Created on: Nov 28, 2011
 *      Author: suz
 */

#ifndef COSINE_H_
#define COSINE_H_

#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>	// for pow and sqrt
#include "../../retrieve/ForwardIndex.h"
#include "../../retrieve/InvertedIndex.h"

using namespace std;

class Cosine {
private:
	map<size_t, size_t> computeQueryFreq(vector<size_t> query, set<size_t> uniQuery);
	float computeDenominator(set<size_t> uniTermId, map<size_t, size_t> uniTermFreq);

	void computeScore(size_t docId);
	vector<string> queryTerm;
	vector<size_t> queryTermId;
	set<size_t> uniQueryTermId;
	map<size_t, size_t> uniQueryTermFreq;
	float queryDenominator;
	vector<float> score;

	ForwardIndex* frwdReader;
	InvertedIndex invtReader;
public:
	Cosine();
	virtual ~Cosine();
	void setup(set<size_t> binResult, vector<size_t> queryId, vector<string>queryTerm, ForwardIndex* fR);
	vector<float> getScore();
};

#endif /* COSINE_H_ */
