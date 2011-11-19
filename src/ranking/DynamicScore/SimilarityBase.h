/*
 * SimilarityBase.h
 *
 *  Created on: Oct 15, 2011
 *      Author: suz
 */

#ifndef SIMILARITYBASE_H_
#define SIMILARITYBASE_H_

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

class SimilarityBase {
private:
	//private vars
	struct sim_doc_pair{
		size_t docId;
		float score;
		bool operator () (const sim_doc_pair& lhs , const sim_doc_pair& rhs) // replace YourStruct
		{
		return lhs.score < rhs.score;
		}
	};
	std::vector<size_t> docID;
	std::vector<size_t> termID;
	std::vector<std::vector<float> > tf;
	std::vector<std::vector<float> > df;

	//private methods
	virtual void getDynamicStatistics();
	virtual void getStaticStatistics();

protected:
	//protected vars
	size_t N;	//document number
	size_t M;	//term number
	std::vector<SimilarityBase::sim_doc_pair> similarity;

public:
	//public methods
	SimilarityBase();
	SimilarityBase(std::vector<size_t> docID, std::vector<size_t> termID);
	virtual ~SimilarityBase();

	virtual std::vector<std::vector<float> > getIdf();
	virtual std::vector<std::vector<float> > getTfIdf(std::vector<std::vector<float> >& idf);
	virtual std::vector<std::vector<float> > getWf();
	virtual std::vector<std::vector<float> > getWftd(std::vector<std::vector<float> >& wf);
	virtual std::vector<SimilarityBase::sim_doc_pair> getSimilarity();	//dummy waiting to be override.
	virtual std::vector<size_t> getRank(int k); //return top kth results.

	virtual void setDocID(std::vector<size_t> docID);
	virtual void setTermID(std::vector<size_t> termID);

	virtual void computeSimilarity();
};

#endif /* SIMILARITYBASE_H_ */
