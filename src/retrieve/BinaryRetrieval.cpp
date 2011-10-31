/*
 * BinaryRetrieval.cpp
 *
 *  Created on: Oct 30, 2011
 *      Author: bhatt
 */

#include "BinaryRetrieval.h"

BinaryRetrieval::BinaryRetrieval() {
	// TODO Auto-generated constructor stub

}

BinaryRetrieval::~BinaryRetrieval() {
	// TODO Auto-generated destructor stub
}

list<size_t> BinaryRetrieval::search(vector<list<size_t> > postings){

	list<size_t> result;
	list<size_t> tmp;

	size_t min;
	size_t allCount=0;
	size_t lastPopedDocId;
	bool alive;

	while(true){
	alive = false;
	min = 9999999999;
	for(size_t k=0;k<postings.size();k++){
		tmp = postings.at(k);
		if(tmp.size()>0 && tmp.front()<min){
			min = tmp.front();
			alive = true;
		}
	}
	//cout<<"min-"<<min<<endl;
	if(!alive) break;
	allCount = 0;

	for(size_t k=0;k<postings.size();k++){
		tmp = postings.at(k);
		//cout<<"front:"<<tmp.front()<<endl;
		if(tmp.size()>0 && tmp.front()==min){
			allCount++;
			tmp.pop_front();
			postings.at(k) = tmp;
		}

	}

	if(allCount==postings.size()){
		//doc contains all query terms
		result.push_back(min);
	}
	}

	return result;


}
/**

int main(){
	BinaryRetrieval bn;

	vector<list<size_t> > test;

	list<size_t> list1;
	list1.push_back(12);
	list1.push_back(17);
	list1.push_back(18);
	list1.push_back(20);

	list<size_t> list2;
		list2.push_back(15);
		list2.push_back(17);
		list2.push_back(18);
		list2.push_back(20);



		list<size_t> list3;
			list3.push_back(10);
			list3.push_back(17);
			list3.push_back(18);
			list3.push_back(20);

	test.push_back(list1);
	test.push_back(list2);
	test.push_back(list3);

	list<size_t> results = bn.search(test);


	cout<<"total matches " << results.size()<<endl;


}

*/
