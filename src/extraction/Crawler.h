/*
 * Crawler.h
 *
 *  Created on: Sep 18, 2011
 *      Author: bhatt
 */

#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "../utilities/Library.h"

using namespace std;

class Crawler {
public:
	Crawler();
	virtual ~Crawler();
	void read(std::string source);

};

#endif /* CRAWLER_H_ */
