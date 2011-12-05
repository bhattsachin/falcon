/*
 * Cosine.cpp
 *
 *  Created on: Nov 28, 2011
 *      Author: suz
 */

#include "Cosine.h"

Cosine::Cosine() {
	// TODO Auto-generated constructor stub
}

Cosine::~Cosine() {
	// TODO Auto-generated destructor stub
}

void Cosine::setup(set<size_t> binResult, vector<size_t> queryTermId, vector<string>queryTerm, ForwardIndex* fR){
	// TODO set the list of binary search result and the query term Ids.
	//		Calculate the scores for each documents in binResult.
	this->frwdReader = fR;
	this->frwdReader->setup(1,"OUTPUT/fwd_index/ForwardIndex.txt");
	this->queryTerm = queryTerm;
	sort(queryTermId.begin(), queryTermId.end());
	this->queryTermId = queryTermId;
	// make query terms unique
	for(vector<size_t>::iterator it = queryTermId.begin(); it!=queryTermId.end(); ++it){
		this->uniQueryTermId.insert(*it);
	}
	this->uniQueryTermFreq = Cosine::computeQueryFreq(this->queryTermId, uniQueryTermId);
	this->queryDenominator = Cosine::computeDenominator(uniQueryTermId, uniQueryTermFreq);
	// for each document in binary search result list, apply "computeScore"
	for(set<size_t>::iterator itBinResult = binResult.begin(); itBinResult!=binResult.end(); ++itBinResult){
		computeScore(*itBinResult);
	}
}

map<size_t, size_t> Cosine::computeQueryFreq(vector<size_t> query, set<size_t> uniQuery){
	// TODO given a vector of query term ids, return the query term frequency.
	//		ISSUE: can be more effective! -- Nov 28, 2011
	map<size_t, size_t> score;

	set<size_t>::iterator itUniQuery = uniQuery.begin();
	for (; itUniQuery!=uniQuery.end(); ++itUniQuery){
		vector<size_t>::iterator itQuery = query.begin();
		size_t tempCount = 0;
		for(; itQuery!=query.end(); ++itQuery){
			if (*itUniQuery == *itQuery){
				tempCount++;
			}
		}
		score[*itUniQuery] = tempCount; // push back term frequency
	}

	return score;
}

float Cosine::computeDenominator(set<size_t> uniTermId, map<size_t, size_t> uniTermFreq){
	// TODO given a map of unique term frequency and return the normalizer of the query sequence
	float rtr=0;
	set<size_t>::iterator itUq = uniTermId.begin();
	for (; itUq != uniTermId.end(); ++itUq){
		rtr += pow((float)uniTermFreq[*itUq], 2);
	}
	rtr = sqrt(rtr)/uniTermId.size();
	return rtr;
}

void Cosine::computeScore(size_t docId){
	// TODO given a doc Id, compute the score of this doc.
	float cossim=0;

	// get forward index and make it unique
	set<size_t> frwdIndx =this->frwdReader->getUniqueTermId(docId);

	// get term frequency
	//	!!! need an interface..
	map<size_t, size_t> docTermFreq;
	set<size_t>::iterator itDocTermFreq = frwdIndx.begin();
	size_t count = 0;
	for (; itDocTermFreq!=frwdIndx.end(); ++itDocTermFreq){
		docTermFreq[*itDocTermFreq] = this->invtReader.getTF(this->queryTerm.at(count), docId);
		//docTermFreq[*itDocTermFreq] = 1;
		++count;
	}

	// intersection of two sets
	vector<size_t> interTermId(min(this->uniQueryTermId.size(), frwdIndx.size()));
	vector<size_t>::iterator itInterset;
	itInterset = set_intersection (this->uniQueryTermId.begin(), this->uniQueryTermId.end(), frwdIndx.begin(), frwdIndx.end(), interTermId.begin());
	interTermId.erase(itInterset, interTermId.end());

	// compute un-normalized cosine similarity
	itInterset = interTermId.begin();
	for(; itInterset!=interTermId.end(); ++itInterset){
		cossim += (docTermFreq[*itInterset] * this->uniQueryTermFreq[*itInterset]);
	}

	// compute the denominators for current document
	float docDenominator = computeDenominator(frwdIndx, docTermFreq);

	// push back the scores into member variant
	cout << "iterset num: " << interTermId.size() <<"  || q term num: " << uniQueryTermId.size() << " || uniqdoctermId: " << frwdIndx.size() << endl;
	cout << "unnorm cossim: " << cossim;
	cossim = cossim / docDenominator /this->queryDenominator;
	cout << " |||| docDenom: " << docDenominator << " |||| queryDenom: "<<this->queryDenominator<<endl;
	this->score.push_back(cossim);
}

vector<float> Cosine::getScore(){
	// TODO public, return the score
	sort(score.begin(), score.end());
	return this->score;
}
