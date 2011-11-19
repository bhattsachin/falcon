/*
 * SimilarityCosine.h
 *
 *  Created on: Oct 15, 2011
 *      Author: suz
 */

#ifndef SIMILARITYCOSINE_H_
#define SIMILARITYCOSINE_H_

#include "SimilarityBase.h"

class SimilarityCosine: public SimilarityBase::SimilarityBase {
public:
	SimilarityCosine();
	SimilarityCosine(std::vector<size_t> docID, std::vector<size_t> termID);
	virtual ~SimilarityCosine();
	virtual void computeSimilarity();
};

#endif /* SIMILARITYCOSINE_H_ */
