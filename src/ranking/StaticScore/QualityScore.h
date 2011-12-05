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
	QualityScore() : ScoreBase(){};
	virtual ~QualityScore();
	virtual float getScore();
};

#endif /* QUALITYSCORE_H_ */
