/*
 * CommandLine.cpp
 *
 *  Created on: Oct 29, 2011
 *      Author: bhatt
 */

#include "CommandLine.h"


string EXIT = "exit";
CommandLine::CommandLine() {
	idex.load();
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
		result = " ";
		cout<<"~ falcon$ ";
		cin>>command;
		time(&start);

		//send query for evaulation & return the result;
		result = runQuery(command);

		cout<<"~ result$: "<<result<<endl;
		time(&end);
		diff = difftime(end,start);
		cout<<diff<<" seconds elapsed."<<endl;


	}while(EXIT.compare(command)!=0);

	//cout<<"--terminating falcon---hope you like it :)--give us good marks"<<endl;

}



string CommandLine::runQuery(string query){
	qparser.setQueryString(query);
	vector<string> queryTerms = qparser.getTerms();

	//cout<<"----------total terms:"<<queryTerms.size()<<": term:"<<queryTerms.at(0)<<endl;

	vector<list<size_t> > postingList;

	for(size_t j=0;j<queryTerms.size();j++){
		//cout<<"query parser returns::"<<queryTerms.at(j)<<endl;
		postingList.push_back(idex.getPostingList(queryTerms.at(j)));
	}

	list<size_t> m_result;
	m_result = bret.search(postingList);

	string response;
	response = m_result.size() + " results found";
	cout<<response<<endl;

	return response;

}

/**
int main(){

	CommandLine cmd;
	cmd.run();

}
 */
