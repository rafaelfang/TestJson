/*
 * Alignment.h
 *
 *  Created on: Mar 9, 2015
 *      Author: Chao
 */

#ifndef TESTBLAST_ALIGNMENTTOOL_H_
#define TESTBLAST_ALIGNMENTTOOL_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
using namespace std;

class AlignmentTool {
public:
	//constructor
	AlignmentTool(char*);


	virtual ~AlignmentTool();

	virtual void jsonParser() =0;
	virtual void readFastaFile(string)=0;
	virtual void executeAlignment()=0;


protected:
	char* jsonFileName;
	string proteinName;
	string aminoAcids;
};

#endif /* TESTBLAST_ALIGNMENTTOOL_H_ */
