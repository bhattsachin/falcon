/*
 * ScoreWriter.h
 *
 *  Created on: Nov 26, 2011
 *      Author: suz
 */

#ifndef SCOREWRITER_H_
#define SCOREWRITER_H_
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "../../utilities/FileUtil.h"

using namespace std;
class ScoreWriter {
private:
	FileUtil fUtil;
	ofstream ofs;

public:
	ScoreWriter();
	ScoreWriter(string outputFile);
	virtual ~ScoreWriter();
	virtual void init (string outputFile);
	virtual void writeScoreFile(size_t docId, float score);
	virtual void closeFile();
};

#endif /* SCOREWRITER_H_ */
