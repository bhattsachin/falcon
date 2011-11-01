/*
 * Util.cpp
 *
 *  Created on: Oct 26, 2011
 *      Author: bhatt
 */

#include "Util.h"
#include <iostream>

using namespace std;
Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

bool Util::parseCommandLine(int argc, char** argv){
	string BATCH_MODE="-r";
	string INTERACTIVE_MODE="-s";
	string INDEXING_MODE="-i";
	bool validQuery = false;
	for(int i = 0; i < argc; i++)
	      cout << "argv[" << i << "] = " << argv[i] << endl;

	if((BATCH_MODE.compare(argv[1])!=0 || INTERACTIVE_MODE.compare(argv[1])!=0 || INDEXING_MODE.compare(argv[1])!=0) && argc>1){
		validQuery = true;

		if(argv[1]=="-r"){
			//batch mode
			//verify for two more arguments
			if(argc==3)
				validQuery = true;

		}else{
			if(argc==2)
				validQuery = true;
		}

	}
	return validQuery;

}

/**
int main(){

	vector<string> lst;
	lst.push_back("sun");
	lst.push_back("mon");
	lst.push_back("tue");
	lst.push_back("sun");
	lst.push_back("sun");
	lst.push_back("mon");
	lst.push_back("fri");
	lst.push_back("dry");


	map<string,size_t> count;
	map<string,size_t>::iterator iter;

	for(size_t m=0;m<lst.size();m++){
		if(count.find(lst.at(m))!=count.end()){
			count.find(lst.at(m))->second = count.find(lst.at(m))->second + 1;

		}else{
			count.insert(pair<string,size_t>(lst.at(m),1));
		}
	}


	for(iter = count.begin();iter!=count.end();iter++){
		cout<<iter->first<<" "<<iter->second<<endl;
	}

	cout<<count["sun"]<<endl;



}
*/
