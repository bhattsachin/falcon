/*
 * CommandLine.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: bhatt
 */

#include "CommandLine.h"

string EXIT = "exit";
CommandLine::CommandLine() {
	// TODO Auto-generated constructor stub

}

CommandLine::~CommandLine() {
	// TODO Auto-generated destructor stub
}

void CommandLine::run(){
	string command;
	time_t start, end;
	string result = "Response of the query here";
	double diff;

	do{
	cout<<"~ falcon$ ";
	cin>>command;
	time(&start);

	//send query for evaulation & return the result;

	cout<<"~ result$: "<<result<<endl;
	time(&end);
	diff = difftime(end,start);
	cout<<diff<<" seconds elapsed."<<endl;

	}while(EXIT.compare(command)!=0);

	cout<<"--terminating falcon---hope you like it :)--give us good marks"<<endl;

}

int main(){

	CommandLine cmd;
	cmd.run();

}
