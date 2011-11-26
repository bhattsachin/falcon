/*
 * QualityScore.cpp
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#include "QualityScore.h"

QualityScore::~QualityScore() {
	// TODO Auto-generated destructor stub
}

float QualityScore::getScore(){
	// TODO return quality score of a wiki file
	this->staticScore = QualityScore::getNumRefer() + QualityScore::getNumSection();
	return QualityScore::staticScore;
}

