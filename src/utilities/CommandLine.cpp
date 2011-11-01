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
	//vector<string> queryTerms = ;
	qparser.setQueryString(query);
	vector<string> queryTerms = qparser.getTerms();

	cout<<"size after dictionary check:"<<queryTerms.size()<<endl;




	//commenting query parser for a while

	/**
	istringstream iss(query);
	copy(istream_iterator<string>(iss),
	         istream_iterator<string>(),
	         back_inserter<vector<string> >(queryTerms));
	*/


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

CommandLine::Query CommandLine::parseQuery(string query){

	//the sequence of input should look like

	//[] number of results
	//<query>
	//[options]

	list<size_t> inputPattern;
	inputPattern.push_back(1);
	inputPattern.push_back(2);
	inputPattern.push_back(3);

	//input pattern added

	CommandLine::Query fullQuery;
	CommandLine::KeyValue optionMap;


	 	string buffer;
	 	string key;
	 	string val;
	 	size_t found;

	 	for(size_t c=0;c<query.size();c++){

	 		if(query.at(c)=='<'){
	 			buffer = "";

	 			//we have entered query input part
	 			//ignore if not entered number of items & add a default value;
	 			if(inputPattern.front()==1){
	 				inputPattern.pop_front();
	 				//setting default value
	 				fullQuery.resultCount = 10;
	 			}
	 		}else if(query.at(c)=='['){
	 			buffer="";

	 		}else if(query.at(c)=='>'){

	 			//this option is only for query part
	 			fullQuery.queryString = buffer;
	 			if(inputPattern.front()==2){
	 				 inputPattern.pop_front();
	 			}

	 		}else if(query.at(c)==']'){

	 			if(inputPattern.front()==1){
	 				fullQuery.resultCount = atoi(buffer.c_str());
	 				inputPattern.pop_front();
	 			}else{
	 				//buffer has the format like opt=value
	 				//can u please split that
	 				found = buffer.find_first_of("=");
	 				if(found!=string::npos){
	 					key = buffer.substr(0,found);
	 					val = buffer.substr(found+1,buffer.length());
	 					optionMap.key = key;
	 					optionMap.val = val;
	 					if(inputPattern.front()==3){
	 						fullQuery.options.push_back(optionMap);
	 					}
	 				}
	 			}
	 		}else{
	 			buffer +=query.at(c);

	 		}
	}
/**
	 	cout<<"resultCount: "<<fullQuery.resultCount<<endl;
	 	cout<<"query: "<<fullQuery.queryString<<endl;
	 	while(fullQuery.options.size()>0){
	 		optionMap = fullQuery.options.front();
	 		cout<<"option: "<<optionMap.key<< " val:"<<optionMap.val<<endl;
	 		fullQuery.options.pop_front();

	 	}
*/

}

/**

 int main(){

 CommandLine cmd;

 //parseQuery
 cout<<"Query: "<<"[10] <buffalo new york>"<<endl;
 cmd.parseQuery("[10] <buffalo new york>");
 cout<<"Query: "<<"[20] <buffalo new york> [author=pradipto]"<<endl;
 cmd.parseQuery("[20] <buffalo new york> [author=pradipto]");
 cout<<"Query: "<<"[15] <buffalo new york> [author=pradipto] [category=city]"<<endl;
 cmd.parseQuery("[15] <buffalo new york> [author=pradipto] [category=city]");

 cmd.parseQuery("<buffalo new york> [authorpradipto] [category=city]");

}

*/



 /**
  * [10] <buffalo new york>
	[20] <buffalo new york> [author=pradipto]
	[15] <buffalo new york> [author=pradipto] [category=city]
  *
  */



