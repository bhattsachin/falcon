/*
 * SimilarityCosine.cpp
 *
 *  Created on: Oct 15, 2011
 *      Author: suz
 */

#include "SimilarityCosine.h"

SimilarityCosine::SimilarityCosine() {// super class constructor will be called automatically
	// TODO Auto-generated constructor stub
}

SimilarityCosine::SimilarityCosine(std::vector<size_t> docID, std::vector<size_t> termID)
: SimilarityBase(docID, termID){ // call super class constructor with arguments
	// TODO argumented constructor
}

SimilarityCosine::~SimilarityCosine() {
	// TODO Auto-generated destructor stub
}

void SimilarityCosine::computeSimilarity() { // override 'computeSimilarity' from 'SimilarityBase'
	// TODO compute cosine similarity
	std::vector<std::vector<float> > a;

	a = getIdf();

	std::vector<std::vector<float> >& ar = a;

	std::vector<std::vector<float> > tfidf;
	tfidf = getTfIdf(ar);

	a = getWf();
	std::vector<std::vector<float> > wftd;
	wftd = getWftd(ar);

	for (size_t i=0; i<N; i++){ // for each DOC
		float tempScore;
		for (size_t j=0; j<M; j++){ // for each query term
				tempScore += tfidf[i][j]*wftd[i][j];
		}
		similarity[i].score = tempScore;
	}
}
