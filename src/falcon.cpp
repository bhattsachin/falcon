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
#include "controller/ParsingIndexingBoostController.h"
#include "parser/lang/en/PositionalTextParser.h"
using namespace std;

string BATCH_MODE = "-r";
string INTERACTIVE_MODE = "-s";
string INDEXING_MODE = "-i";


int main(int argc, char** argv) {
	time_t start, end;
	double diff;
	Util util;
	//filter to test if the command line arguments are correct
	if (!util.parseCommandLine(argc, argv)) {
		cout
				<< "USAGE:   /falcon [-r] <config filename> [batch query]. Or. /falcon [-s] <config filename> "
				<< endl;
		return 0;
	}

	string base_dir = argv[2];
	time(&start);

	if (INDEXING_MODE.compare(argv[1]) == 0) {

		ParsingIndexingBoostController contoller;
		contoller.configureEngine(base_dir);

		//merge all inverted indexes.
		FileUtil fUtil;
		cout << "merging indexes...... (this might take some time)" << endl;
		fUtil.mergeInvertedIndex("index.inv.000");
		fUtil.mergeInvertedIndex("index.inv.001");
		fUtil.mergeInvertedIndex("index.inv.002");
		fUtil.mergeInvertedIndex("index.inv.003");
		fUtil.mergeInvertedIndex("index.inv.004");

	}


	if (INTERACTIVE_MODE.compare(argv[1]) == 0) {
		cout << "Indexed loaded in " << diff << " seconds." << endl;
		CommandLine cl;
		cl.run();
	} else if (BATCH_MODE.compare(argv[1]) == 0) {
		cout << "Indexed loaded in " << diff << " seconds." << endl;
		CommandLine cl;
		time(&end);
		diff = difftime(end, start);

		//read from batch query & print here
		cout << cl.runQuery("President") << endl;
		cout << "Total time taken for execution:" << diff << " seconds" << endl;
	} else {
		//this is default indexing mode.
		//we do nothing here
		time(&end);
		diff = difftime(end, start);

		cout << "Total time taken for execution:" << diff << " seconds" << endl;
	}



	//test block over


}



