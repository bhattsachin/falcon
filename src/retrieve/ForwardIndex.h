/*
 * ForwardIndex.h
 *
 *  Created on: Dec 4, 2011
 *      Author: suz
 */

#ifndef FORWARDINDEX_H_
#define FORWARDINDEX_H_

#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

class ForwardIndex {
private:
	size_t offset;
	std::string fInxUrl;
	std::ifstream ifs;

public:
	ForwardIndex();
	virtual ~ForwardIndex();
	void setup(size_t offset, std::string fInxUrl);
	std::set<size_t> getUniqueTermId(size_t docId);
};

#endif /* FORWARDINDEX_H_ */
