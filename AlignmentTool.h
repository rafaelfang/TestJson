/*
 * Alignment.h
 *
 *  Created on: Mar 9, 2015
 *      Author: Chao
 */

#ifndef ALIGNMENTTOOL_H_
#define ALIGNMENTTOOL_H_

using namespace std;

class AlignmentTool {
public:
	//constructor
	AlignmentTool(char*);


	virtual ~AlignmentTool();

	virtual void jsonParser() const=0;
	virtual void print() const;
	char* getJsonFileName() const;
	void setJsonFileName(char* jsonFileName);

protected:
	char* jsonFileName;
};

#endif /* ALIGNMENTTOOL_H_ */
