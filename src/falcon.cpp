/*
 * RunServer.cpp
 *
 *  Created on: Sep 16, 2011
 *      Author: bhatt
 */

/**
 * Entry point for this engine
 * configures controller based on config files
 * initializes required instances & calls required classes
 */
#include "utilities/Library.h"
#include "utilities/Util.h"
#include "utilities/FileUtil.h"
#include "utilities/CommandLine.h"
#include "controller/ParsingIndexingController.h"
#include "parser/lang/en/PositionalTextParser.h"
using namespace std;

string BATCH_MODE="-r";
string INTERACTIVE_MODE="-s";


int main(int argc, char** argv) {
	time_t start, end;
	double diff;
	Util util;
	//filter to test if the command line arguments are correct
	if(!util.parseCommandLine(argc, argv)){
		cout << "USAGE:   /falcon [-r] <config filename> [batch query]. Or. /falcon [-s] <config filename> " << endl;
		return 0;
	}

	string base_dir = argv[2];
	time(&start);
	ParsingIndexingController contoller;
	contoller.configureEngine(base_dir);

	//merge all inverted indexes.
	FileUtil fUtil;

	fUtil.mergeInvertedIndex("index.inv.000");
	fUtil.mergeInvertedIndex("index.inv.001");
	fUtil.mergeInvertedIndex("index.inv.002");
	fUtil.mergeInvertedIndex("index.inv.003");
	fUtil.mergeInvertedIndex("index.inv.004");

	//
	PositionalTextParser parser;
	//parser.parse("./data/news/FT911-119");


	time(&end);
	diff = difftime(end, start);

	if(INTERACTIVE_MODE.compare(argv[1])==0){
		cout<<"Indexed loaded in "<<diff<<" seconds."<<endl;
		CommandLine cl;
		cl.run();
	}else{

		cout << "Total time taken for execution:" << diff << " seconds" << endl;
	}

	//test block over


}




