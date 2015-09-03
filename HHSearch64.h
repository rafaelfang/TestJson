/*
 * HHSearch64.h
 *
 *  Created on: Mar 13, 2015
 *      Author: Chao
 */

#ifndef TESTBLAST_HHSEARCH64_H_
#define TESTBLAST_HHSEARCH64_H_
#include <assert.h>
#include <iostream>
#include <fstream>

#include "AlignmentTool.h"
#include "json/json.h"
#include "Utility.h"
class HHSearch64: public AlignmentTool {
public:
	HHSearch64(char*);
	virtual void jsonParser();

	void setJsonFilename(string);
	void runAlignHits();
	void runHHMake();
	void runHHSearch(string const);
	virtual void executeAlignment(string);
	virtual void generateIndividualProteinFolder();
	virtual ~HHSearch64();
private:
	string jsonFilename;
	string fastaFilename;
	string fastaFileLocation;
	string alignhitsParameterList;
	string hhmakeParameterList;
	string hhsearchParameterList;
	string alignmentToolLocation;
	string databaseLocation;
	string experimentLocation;
	string _a3m;
};

#endif /* TESTBLAST_HHSEARCH64_H_ */
