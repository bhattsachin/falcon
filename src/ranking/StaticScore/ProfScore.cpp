/*
 * ProfScore.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#include "ProfScore.h"

ProfScore::~ProfScore() {
	// TODO Auto-generated destructor stub
}

float ProfScore::getScore(){
	// TODO return professional score of a file
	return ProfScore::JCoeffient(getCatList(), getWikiBody());
}

float ProfScore::JCoeffient(set<size_t> A, set<size_t> B){
	// TODO implementation of Jaccard Coefficient
	float score=0.0;
	int totalSize = A.size() + B.size();
	vector<size_t> v(totalSize);
	vector<size_t>::iterator it;
	it = set_intersection(A.begin(), A.end(), B.begin(), B.end(), v.begin());
	int intersection = int(it - v.begin());
	score = intersection / totalSize;
	return score;
}

