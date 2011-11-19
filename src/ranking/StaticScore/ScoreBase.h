/*
 * ScoreBase.h
 *
 *  Created on: Nov 19, 2011
 *      Author: suz
 */

#ifndef SCOREBASE_H_
#define SCOREBASE_H_

class ScoreBase {
public:
	ScoreBase();
	virtual ~ScoreBase();
	float getScore();

private:
	float staticScore;
};

#endif /* SCOREBASE_H_ */
