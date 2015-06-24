/*
 * CNFSearch.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: cf797
 */

#include "CNFSearch.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "json/json.h"
#include "Utility.h"

CNFSearch::CNFSearch(char* rootName) :
		AlignmentTool(rootName) {
	fastaFilename = rootName;
	fastaFilename += ".fasta";

}

CNFSearch::~CNFSearch() {
	// TODO Auto-generated destructor stub
}
void CNFSearch::generateIndividualProteinFolder() {
	string individualProteinPath = "mkdir -p ";
	individualProteinPath += experimentLocation;
	individualProteinPath += "/";
	individualProteinPath += rootName;
	Utility utility;
	char* cmd = utility.convertStringToCharArr(individualProteinPath);
	printf("%s\n", cmd);
	system(cmd);
}
void CNFSearch::setJsonFilename(string theJsonFilename) {
	jsonFilename = theJsonFilename;
}

void CNFSearch::jsonParser() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {

		//cout<<fastaFilename<<endl;
		alignmentToolLocation = root["alignmentToolLocation"].asString();
		databaseLocation = root["databaseLocation"].asString();
		experimentLocation = root["experimentLocation"].asString();
		fastaFileLocation = root["fastaFileLocation"].asString();

	}

	is.close();
}

void CNFSearch::runBuildFeature() {

	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {
		buildFeatureParameterList = "./buildFeature ";

		for (Json::Value::iterator it =
				root["buildFeaturesParameterSetting"].begin();
				it != root["buildFeaturesParameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-i") == 0) {
				buildFeatureParameterList += " -i ";
				buildFeatureParameterList += fastaFileLocation;
				buildFeatureParameterList += "/";
				buildFeatureParameterList += rootName;
				buildFeatureParameterList += ".fasta";

			} else if (tempKey.compare("-c") == 0) {
				buildFeatureParameterList += " -c ";
				buildFeatureParameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				buildFeatureParameterList += " -o ";
				buildFeatureParameterList += experimentLocation;
				buildFeatureParameterList += "/";
				buildFeatureParameterList += rootName;
				buildFeatureParameterList += "/";
				buildFeatureParameterList += rootName;
				buildFeatureParameterList += ".tgt";

			}

		}
	}
	is.close();

	//change to tool install location
	string toolLocation = alignmentToolLocation;

	char* cmd1 = (char*) toolLocation.c_str();
	int ret = chdir(cmd1);
	//printf("%s\n", cmd1);
	//cout<<ret<<endl;
	//system("pwd");
	cout<<"build feature start on target "<<rootName<<endl;

	//build features
	Utility utility;
	char* cmd = utility.convertStringToCharArr(buildFeatureParameterList);
	system(cmd);
	//printf("%s\n", cmd);
	cout<<"build feature on target "<<rootName<<" end"<<endl;
}

void CNFSearch::runCNFSearch() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {
		cnfSearchParameterList = alignmentToolLocation;
		cnfSearchParameterList += "CNFsearch ";
		//"%shhsearch -i %squery.hhm -d %scal.hhm -cal -o %squery.hhrNR",
		for (Json::Value::iterator it =
				root["CNFSearchParameterSetting"].begin();
				it != root["CNFSearchParameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-a") == 0) {
				cnfSearchParameterList += " -a ";
				cnfSearchParameterList += tempValue;
			} else if (tempKey.compare("-q") == 0) {
				cnfSearchParameterList += " -q ";
				cnfSearchParameterList += rootName;

			} else if (tempKey.compare("-p") == 0) {
				cnfSearchParameterList += " -p ";
				cnfSearchParameterList += tempValue;
			} else if (tempKey.compare("-g") == 0) {
				cnfSearchParameterList += " -g ";
				cnfSearchParameterList += experimentLocation;
				cnfSearchParameterList += "/";
				cnfSearchParameterList += rootName;
				cnfSearchParameterList += "/";
			} else if (tempKey.compare("-o") == 0) {
				cnfSearchParameterList += " -o ";
				cnfSearchParameterList += experimentLocation;
				cnfSearchParameterList += "/";
				cnfSearchParameterList += rootName;
				cnfSearchParameterList += "/query.rank";

			} else if (tempKey.compare("-d") == 0) {
				cnfSearchParameterList += " -d ";
				cnfSearchParameterList += databaseLocation;
				cnfSearchParameterList += "/";
				cnfSearchParameterList += tempValue;
				cnfSearchParameterList += "/";

			} else if (tempKey.compare("-l") == 0) {
				cnfSearchParameterList += " -l ";
				cnfSearchParameterList += databaseLocation;
				cnfSearchParameterList += "/";
				cnfSearchParameterList += tempValue;

			} else if (tempKey.compare("-n") == 0) {
				cnfSearchParameterList += " -n ";
				cnfSearchParameterList += tempValue;

			}

		}
	}
	is.close();

	//change to tool install location
	string toolLocation = alignmentToolLocation;
	cout<<"cnfsearch start on target "<<rootName<<endl;
	char* cmd1 = (char*) toolLocation.c_str();
	int ret = chdir(cmd1);
	printf("%s\n", cmd1);
	//cout<<ret<<endl;
	//system("pwd");

	char* cmd = (char*) cnfSearchParameterList.c_str();
	system(cmd);
	//printf("%s\n", cmd);
	cout<<"cnfsearch on target "<<rootName<<" finish"<<endl;
}
void CNFSearch::executeAlignment(string configFile) {
	setJsonFilename(configFile);
	jsonParser();

	runBuildFeature();
	runCNFSearch();

}
