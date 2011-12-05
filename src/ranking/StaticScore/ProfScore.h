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
	ProfScore() : ScoreBase(){};
	virtual ~ProfScore();
	virtual float getScore();

private:
	float JCoeffient(set<size_t> A, set<size_t> B);
};


#endif /* PROFSCORE_H_ */
