/*
 * DocumentQueue.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: bhatt
 */

#include "DocumentQueue.h"

using namespace std;

DocumentQueue::DocumentQueue() {
	// TODO Auto-generated constructor stub

}

DocumentQueue::~DocumentQueue() {
	// TODO Auto-generated destructor stub
}

void DocumentQueue::addToQueue(size_t id, string type, string path) {
	Document d;
	d.id = id;
	d.type = type;
	d.path = path;
	vector<DocumentQueue::Document>* queue = getQueue();

	queue->push_back(d);
	//cout<<"*****data inserted:"<<queue->size();
	//getQueue().insert(d);
	//cout<<endl<<"#added to task queue : id->"<<d.id<<" type->"<<d.type<<" path->"<<d.path<<endl;

}
