/*
 * SimilarityBase.cpp
 *
 *  Created on: Oct 15, 2011
 *      Author: suz
 */

#include "SimilarityBase.h"

SimilarityBase::SimilarityBase() {
	// TODO Auto-generated constructor stub
	SimilarityBase::getStaticStatistics();
}

SimilarityBase::SimilarityBase(std::vector<size_t> docIDv, std::vector<size_t> termIDv){
	// TODO constructor with paramaters
	SimilarityBase::getStaticStatistics();
	SimilarityBase::setDocID(docIDv);
	SimilarityBase::setTermID(termIDv);
	SimilarityBase::getDynamicStatistics();
}

SimilarityBase::~SimilarityBase() {
	// TODO Auto-generated destructor stub
}

void SimilarityBase::getDynamicStatistics(){
	// TODO get dynamic statistics of df, tf and from files preallocate similarity vector,
	//		which will be different for different query termIDs and docIDs

	//dummy

	//preallocate similarity vector
	similarity.resize(docID.size());
	for(size_t i=0; i<docID.size(); i++){
		sim_doc_pair tempSDP;
		tempSDP.docId = docID[i];
		tempSDP.score = -1;
		similarity[i] = tempSDP;
	}

}

void SimilarityBase::getStaticStatistics(){
	// TODO get static statistics of M, N from file which won't change except indexes were changed

	//dummy
	this->N = 1000;
	this->M = 500000;

	//init vars
	this->tf.resize(N);
	this->df.resize(N);
	this->similarity.resize(N);
}

std::vector<std::vector<float> > SimilarityBase::getIdf(){
	std::vector<std::vector<float> > idf;
	idf.resize(N);
	std::vector<float> tempDf;
	std::vector<float> tempIdf;
	tempIdf.resize(M);
	for (size_t i = 0; i<N; i++){
		tempDf = df[i];

		for (size_t j=0; j<M; j++){
			tempIdf[j] = log10((float)(N/tempDf[j]));
		}
		idf[i] = tempIdf;
	}
	return idf;
}

std::vector<std::vector<float> > SimilarityBase::getTfIdf(std::vector<std::vector<float> >& idf){
	std::vector<std::vector<float> > tfIdf;
	tfIdf.resize(N);
	std::vector<float> tempTf;
	std::vector<float> tempTfIdf;
	std::vector<float> tempIdf;
	tempTfIdf.resize(M);
	for (size_t i = 0; i<N; i++){
		tempTf = tf[i];
		tempIdf = idf[i];

		for(size_t j=0; j<M; j++){
			tempTfIdf[j] = tempTf[j]*tempIdf[j];
		}

		tfIdf[i] = tempTfIdf;
	}
	return tfIdf;
}

std::vector<std::vector<float> > SimilarityBase::getWf(){ // will be override in high-level classes
	return tf;
}

std::vector<std::vector<float> > SimilarityBase::getWftd(std::vector<std::vector<float> >& wf){
	std::vector<std::vector<float> > wftd;
	wftd.resize(N);
	std::vector<float> tempWftd;
	tempWftd.resize(M);
	size_t tempNormFactor=0;
	for (size_t i = 0; i<N; i++){
		tempNormFactor = 0;
		for(size_t j=0; j<M; j++){
			tempNormFactor += wf[i][j] * wf[i][j];
		}
		for(size_t j=0; j<M; j++){
			tempWftd[j] = wf[i][j]/tempNormFactor;
		}
		wftd[i] = tempWftd;
	}
	return wftd;
}

std::vector<SimilarityBase::sim_doc_pair> SimilarityBase::getSimilarity(){
	return this->similarity;
}

std::vector<size_t> SimilarityBase::getRank(int k){
	std::vector<size_t> rankResult;
	rankResult.resize(k);
	sort(similarity.begin(), similarity.end(), SimilarityBase::sim_doc_pair());//operator () had been override to compare two structures
	return rankResult;
}

void SimilarityBase::computeSimilarity(){
	// TODO compute Scores/similarities, will be over ride by child classes
	//dummy
}


void SimilarityBase::setDocID(std::vector<size_t> docIDv){
	this->docID = docIDv;
}

void SimilarityBase::setTermID(std::vector<size_t> temrIDv){
	this->termID = temrIDv;
}
