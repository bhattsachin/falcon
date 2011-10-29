/*
 * CommandLine.h
 *
 *  Created on: Oct 29, 2011
 *      Author: bhatt
 *
 *      Used for commandline processing of the TREC query
 *      terminates on exit
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include "Library.h";

using namespace std;
class CommandLine {
public:
	CommandLine();
	virtual ~CommandLine();
	void run();
};

#endif /* COMMANDLINE_H_ */
