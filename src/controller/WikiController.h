/*
 * WikiController.h
 *
 *  Created on: Sep 26, 2011
 *      Author: bhatt
 */

#ifndef WIKICONTROLLER_H_
#define WIKICONTROLLER_H_

#include "../utilities/Library.h"

using namespace std;

class WikiController {
public:
	WikiController();
	virtual ~WikiController();
	struct SemWiki{
		string articleName;
		string author;
		string timestamp;
		vector<string> infobox;
		vector<vector<string> > sections;
		vector<string> links;
		vector<string> category;

	};
	void createSemWiki(WikiController::SemWiki);

};

#endif /* WIKICONTROLLER_H_ */
