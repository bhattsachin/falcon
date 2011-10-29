/*
 * TextUtil.cpp
 *
 *  Created on: Oct 28, 2011
 *      Author: bhatt
 */

#include "TextUtil.h"

TextUtil::TextUtil() {

	//<10,term1> , <25, term2>, <40,term3>, <70,term1> , <90,term2>, <135,term3>, <150, term2>
	TextUtil::TermPosition pos;
	pos.position = 10;
	pos.termId = 1001;
	inputData.push_back(pos);

	pos.position = 25;
	pos.termId = 1002;
	inputData.push_back(pos);

	pos.position = 40;
	pos.termId = 1003;
	inputData.push_back(pos);

	pos.position = 70;
	pos.termId = 1001;
	inputData.push_back(pos);

	pos.position = 90;
	pos.termId = 1002;
	inputData.push_back(pos);

	pos.position = 135;
	pos.termId = 1003;
	inputData.push_back(pos);

	pos.position = 150;
	pos.termId = 1002;
	inputData.push_back(pos);

	mincost.cost = 9999999;

}

TextUtil::~TextUtil() {
	// TODO Auto-generated destructor stub
}

void TextUtil::calculateQueryWindow(vector<TextUtil::TermPosition> list,
		size_t min, size_t max,
		map<size_t, vector<TextUtil::TermPosition> >::iterator it) {
	cout << "###max:" << max << " min:" << min << " termId:"
			<< list.at(1).termId << endl;
	map<size_t, vector<TextUtil::TermPosition> >::iterator localIt = it;
	size_t val, m_max, m_min;
	m_max = max;
	m_min = min;
	it++;

	//backtrack for each element
	for (size_t k = 0; k < list.size(); k++) {


		val = list.at(k).position;

		if(localIt==partitionedInputData.begin()){
			m_max = val;
			m_min = val;
		}

		cout<<"term:"<<list.at(k).termId<<" val="<<val<<endl;

		if(m_min > val){
			continue;
		}

		if (m_min > val) {
						m_min = val;
					} else if (m_max < val) {
						m_max = val;

					}



		//if we are not in the last level go deep
		if (it != partitionedInputData.end()) {

			calculateQueryWindow(it->second, m_min, m_max, it);
			cout<<"value we entered with:"<<"max:"<<m_max<<" min:"<<m_min<<endl;

		} else {
			cout << "term:" << list.at(k).termId << " position:"
					<< list.at(k).position << "max:"<<m_max<<" min:"<<m_min<<endl;
			if (mincost.cost > (m_max - m_min)) {
				mincost.cost = m_max - m_min;
				mincost.end_position = m_max;
				mincost.start_position = m_min;
				cout << "#########################setting: " << (m_max - m_min) << endl;
			} else {
				cout << "max-min" << (m_max - m_min) << endl;
			}
		}

	}


}

/**
 * partition the input into different vectors for each term
 */

void TextUtil::partitionData(vector<TextUtil::TermPosition> inputData) {

	for (size_t i = 0; i < inputData.size(); i++) {
		if (partitionedInputData.find(inputData.at(i).termId)
				!= partitionedInputData.end()) {
			vector<TextUtil::TermPosition> oList;
			oList = (partitionedInputData.find(inputData.at(i).termId)->second);
			oList.push_back(inputData.at(i));
			//will this push back the data - nopes that's why c sucks
			partitionedInputData[inputData.at(i).termId] = oList;

		} else {
			vector<TextUtil::TermPosition> list;
			list.push_back(inputData.at(i));
			partitionedInputData.insert(
					pair<size_t, vector<TextUtil::TermPosition> > (
							inputData.at(i).termId, list));
		}

	}

}

/**

int main() {
	TextUtil util;
	map<size_t, vector<TextUtil::TermPosition> >::iterator it;

	util.partitionData(util.inputData);

	for (it = util.partitionedInputData.begin(); it
			!= util.partitionedInputData.end(); it++) {
		vector<TextUtil::TermPosition> data = it->second;
		for (size_t p = 0; p < data.size(); p++) {
			cout << "term " << data.at(p).position << endl;
		}
	}

	it = util.partitionedInputData.begin();
//	cout << "it-second:" << it->second.size() << endl;
	//search best cost
	util.calculateQueryWindow(it->second, it->second.at(0).position, it->second.at(0).position, it);

	cout << "min cost" << util.mincost.cost << endl;
	cout << "start:" << util.mincost.start_position << endl;
	cout << "end position:" << util.mincost.end_position << endl;

	return 0;
}

*/
