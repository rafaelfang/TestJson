/*
 * Blast.h
 *
 *  Created on: Mar 10, 2015
 *      Author: Chao
 */

#ifndef TESTBLAST_BLAST_H_
#define TESTBLAST_BLAST_H_
#include <assert.h>
#include <iostream>
#include <fstream>

#include "AlignmentTool.h"
#include "json/json.h"
#include "Utility.h"
class Blast: public AlignmentTool {
public:
	//constructor
	Blast(char*);
	virtual void jsonParser();
	virtual void readFastaFile(string );
	virtual void executeAlignment();
	virtual ~Blast();

private:
	string fastaFilename;
	string alignmentToolLocation;
	string databaseLocation;
	string experimentLocation;
	string parameterList;

};

#endif /* TESTBLAST_BLAST_H_ */
