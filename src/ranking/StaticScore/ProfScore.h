/*
 * ProfScore.h
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#ifndef PROFSCORE_H_
#define PROFSCORE_H_

#include "ScoreBase.h"

class ProfScore: public ScoreBase {
public:
	ProfScore(vector<ifstream*> ifsPtrList, size_t offset, size_t barrelSize) : ScoreBase(ifsPtrList, offset, barrelSize){};
	virtual ~ProfScore();

private:
	class JOccur{

	};
};


#endif /* PROFSCORE_H_ */
