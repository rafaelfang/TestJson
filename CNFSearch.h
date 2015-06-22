/*
 * CNFSearch.h
 *
 *  Created on: Jun 17, 2015
 *      Author: cf797
 */

#ifndef CNFSEARCH_H_
#define CNFSEARCH_H_

#include <string>

#include "AlignmentTool.h"

class CNFSearch: public AlignmentTool {
public:
	CNFSearch(char*);
	virtual void jsonParser();
	void setJsonFilename(string);
	void runBuildFeature();
	void runCNFSearch();
	virtual void executeAlignment(string);
	virtual void generateIndividualProteinFolder();
	virtual ~CNFSearch();

private:
	string jsonFilename;

	string fastaFileLocation;
	string fastaFilename;
	string buildFeatureParameterList;
	string cnfSearchParameterList;
	string alignmentToolLocation;
	string databaseLocation;
	string experimentLocation;

};

#endif /* CNFSEARCH_H_ */
