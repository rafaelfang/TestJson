/*
 * HHSearch64.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: Chao
 */

#include "HHSearch64.h"

HHSearch64::HHSearch64(char* rootName) :
		AlignmentTool(rootName) {
	// TODO Auto-generated constructor stub
	fastaFilename = rootName;
	fastaFilename += ".fasta";
	jsonFilename = "configHHSearch.json";
}

HHSearch64::~HHSearch64() {
	// TODO Auto-generated destructor stub
}

void HHSearch64::generateIndividualProteinFolder() {
	string individualProteinPath = "mkdir -p ";
	individualProteinPath += experimentLocation;
	individualProteinPath += "/";
	individualProteinPath += rootName;
	Utility utility;
	char* cmd = utility.convertStringToCharArr(individualProteinPath);
	printf("%s\n", cmd);
	system(cmd);
}
void HHSearch64::setJsonFilename(string theJsonFilename) {
	jsonFilename = theJsonFilename;
}


void HHSearch64::jsonParser() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {

		//read info from root
		fastaFilename = root["fastaFilename"].asString();
		//cout<<fastaFilename<<endl;
		alignmentToolLocation = root["alignmentToolLocation"].asString();
		databaseLocation = root["databaseLocation"].asString();
		experimentLocation = root["experimentLocation"].asString();
		fastaFileLocation = root["fastaFileLocation"].asString();
		_a3m = root["-a3m"].asString();

	}

	is.close();
}

void HHSearch64::runAlignHits() {
	alignhitsParameterList = "perl ";
	alignhitsParameterList += alignmentToolLocation;
	alignhitsParameterList += "alignhits.pl ";
	alignhitsParameterList += experimentLocation;
	alignhitsParameterList += "/";
	alignhitsParameterList += rootName;
	alignhitsParameterList += "/";
	alignhitsParameterList += "query.blaPDB ";
	alignhitsParameterList += "-a3m ";
	alignhitsParameterList += experimentLocation;
	alignhitsParameterList += "/";
	alignhitsParameterList += rootName;
	alignhitsParameterList += "/";
	alignhitsParameterList += _a3m;

	Utility utility;
	char* cmd = utility.convertStringToCharArr(alignhitsParameterList);
	system(cmd);
	printf("%s\n", cmd);
}
void HHSearch64::runHHMake() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {
		hhmakeParameterList = alignmentToolLocation;
		hhmakeParameterList += "hhmake";
		for (Json::Value::iterator it = root["HHMakeParameterSetting"].begin();
				it != root["HHMakeParameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-i") == 0) {
				hhmakeParameterList += " -i ";
				hhmakeParameterList += experimentLocation;
				hhmakeParameterList += "/";
				hhmakeParameterList += rootName;
				hhmakeParameterList += "/";
				hhmakeParameterList += tempValue;
			} else if (tempKey.compare("-name") == 0) {
				hhmakeParameterList += " -name ";
				hhmakeParameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				hhmakeParameterList += " -o ";
				hhmakeParameterList += experimentLocation;
				hhmakeParameterList += "/";
				hhmakeParameterList += rootName;
				hhmakeParameterList += "/";
				hhmakeParameterList += tempValue;
			}

		}
	}
	is.close();
	Utility utility;
	char* cmd = utility.convertStringToCharArr(hhmakeParameterList);
	system(cmd);
	printf("%s\n", cmd);
}

void HHSearch64::runHHSearch() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {
		hhsearchParameterList = alignmentToolLocation;
		hhsearchParameterList += "hhsearch ";
		//"%shhsearch -i %squery.hhm -d %scal.hhm -cal -o %squery.hhrNR",
		for (Json::Value::iterator it =
				root["HHSearchParameterSetting"].begin();
				it != root["HHSearchParameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-i") == 0) {
				hhsearchParameterList += " -i ";
				hhsearchParameterList += experimentLocation;
				hhsearchParameterList += "/";
				hhsearchParameterList += rootName;
				hhsearchParameterList += "/";
				hhsearchParameterList += tempValue;
			} else if (tempKey.compare("-d") == 0) {
				hhsearchParameterList += " -d ";
				hhsearchParameterList += databaseLocation;
				hhsearchParameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				hhsearchParameterList += " -o ";
				hhsearchParameterList += experimentLocation;
				hhsearchParameterList += "/";
				hhsearchParameterList += rootName;
				hhsearchParameterList += "/";
				hhsearchParameterList += tempValue;
			} else if (tempKey.compare("-b") == 0) {
				hhsearchParameterList += " -b ";
				hhsearchParameterList += tempValue;
				hhsearchParameterList += " ";
			} else if (tempKey.compare("additional") == 0) {
				hhsearchParameterList += " ";
				hhsearchParameterList += tempValue;
				hhsearchParameterList += " ";
			}

		}
	}
	is.close();

	Utility utility;
	char* cmd = utility.convertStringToCharArr(hhsearchParameterList);
	system(cmd);
	printf("%s\n", cmd);
}

void HHSearch64::executeAlignment(string configFile) {
	setJsonFilename(configFile);
	jsonParser();


	runAlignHits();
	runHHMake();
	runHHSearch();
}
