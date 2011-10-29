/*
 * TextUtil.h
 *
 *  Created on: Oct 28, 2011
 *      Author: bhatt
 */

#ifndef TEXTUTIL_H_
#define TEXTUTIL_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>

//<10,term1> , <25, term2>, <40,term3>, <70,term1> , <90,term2>, <135,term3>, <150, term2>
using namespace std;
class TextUtil {

public:
	struct TermPosition{
		size_t position;
		size_t termId;
	};

	struct QueryWindow{
		size_t start_position;
		size_t end_position;
		size_t cost;
	};

	vector <TermPosition> inputData;
	map<size_t ,vector<TermPosition> > partitionedInputData;
	QueryWindow mincost;

public:
	TextUtil();
	virtual ~TextUtil();
	void calculateQueryWindow(vector<TermPosition> list, size_t min,size_t max, map<size_t, vector<TextUtil::TermPosition> >::iterator it);
public:
	void partitionData(vector<TermPosition> inputData);

};

#endif /* TEXTUTIL_H_ */
