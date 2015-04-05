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

	virtual void executeAlignment(string);
	virtual void generateIndividualProteinFolder();
	void setJsonFilename(string);
	virtual ~Blast();

private:
	string jsonFilename;
	string fastaFilename;
	string alignmentToolLocation;
	string fastaFileLocation;
	string databaseLocation;
	string experimentLocation;
	string parameterList;

};

#endif /* TESTBLAST_BLAST_H_ */
