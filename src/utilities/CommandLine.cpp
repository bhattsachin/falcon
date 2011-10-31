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
	util.loadDictionary("OUTPUT/dictionary/TermDictionary.txt");
}

CommandLine::~CommandLine() {
	// TODO Auto-generated destructor stub
}

void CommandLine::run() {
	string command;
	time_t start, end;
	string result = "Response of the query here";
	double diff;

	do {
		result = " ";
		command = "";
		cout << "~ falcon$ ";
		cin >> command;
		time(&start);

		//send query for evaulation & return the result;
		result = runQuery(command);

		cout << "~ result$: " << result << endl;
		time(&end);
		diff = difftime(end, start);
		cout << diff << " seconds elapsed." << endl;
		cout.flush();

	} while (EXIT.compare(command) != 0);

	//cout<<"--terminating falcon---hope you like it :)--give us good marks"<<endl;

}

string CommandLine::runQuery(string query) {
	//qparser.setQueryString(query);
	//vector<string> queryTerms = qparser.getTerms();
	vector<string> queryTerms;
	//commenting query parser for a while

	istringstream iss(query);
	copy(istream_iterator<string>(iss),
	         istream_iterator<string>(),
	         back_inserter<vector<string> >(queryTerms));



	//code ends

	//cout<<"----------total terms:"<<queryTerms.size()<<": term:"<<queryTerms.at(0)<<endl;

	vector<list<size_t> > postingList;
	//cout<<"query term size:"<<queryTerms.size()<<endl;
	if(queryTerms.size()>0){
	for (size_t j = 0; j < queryTerms.size(); j++) {
		//cout<<"query parser returns::"<<queryTerms.at(j)<<endl;
		postingList.push_back(idex.getPostingList(queryTerms.at(j)));
	}
	}

	list<size_t> m_result;
	string response;

	if (postingList.size() > 0) {
		m_result = bret.search(postingList);
		response = fUtil.getStringValue(m_result.size()) + " results found";

	} else {
		response ="0 results found";
	}

	//response = m_result.size() + " results found";
	//cout << response << endl;

	return response;

}

/**
 int main(){

 CommandLine cmd;
 cmd.run();

 }
 */
