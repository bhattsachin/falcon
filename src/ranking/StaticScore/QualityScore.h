/*
 * QualityScore.h
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#ifndef QUALITYSCORE_H_
#define QUALITYSCORE_H_
#include "ScoreBase.h"

class QualityScore : public ScoreBase {
public:
	QualityScore(vector<ifstream*> ifsPtrList, size_t offset, size_t barrelSize) : ScoreBase(ifsPtrList, offset, barrelSize){};
	virtual ~QualityScore();
};

#endif /* QUALITYSCORE_H_ */
