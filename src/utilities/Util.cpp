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
