/*
 * HHSearch64.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: Chao
 */

#include "HHSearch64.h"

HHSearch64::HHSearch64(char* jsonFileName) :
		AlignmentTool(jsonFileName) {
	// TODO Auto-generated constructor stub

}

HHSearch64::~HHSearch64() {
	// TODO Auto-generated destructor stub
}

void HHSearch64::jsonParser() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFileName, ios::binary);

	if (reader.parse(is, root)) {

		//read info from root
		fastaFilename = root["fastaFilename"].asString();
		//cout<<fastaFilename<<endl;
		alignmentToolLocation = root["alignmentToolLocation"].asString();
		databaseLocation = root["databaseLocation"].asString();
		experimentLocation = root["experimentLocation"].asString();
		_a3m = root["-a3m"].asString();

	}

	is.close();
}
void HHSearch64::setHHSearchLibrary() {
	string libPath = "export HHLIB=";
	libPath += alignmentToolLocation;
	libPath += "/lib/hh";
	Utility utility;
	char* cmd = utility.convertStringToCharArr(libPath);
	system(cmd);
	printf("%s\n", cmd);
}
void HHSearch64::runAlignHits() {
	alignhitsParameterList = "perl ";
	alignhitsParameterList += alignmentToolLocation;
	alignhitsParameterList += "alignhits.pl ";
	alignhitsParameterList += experimentLocation;
	alignhitsParameterList += "query.blaPDB ";
	alignhitsParameterList += "-a3m ";
	alignhitsParameterList += experimentLocation;
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
	is.open(jsonFileName, ios::binary);

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
				hhmakeParameterList += tempValue;
			} else if (tempKey.compare("-name") == 0) {
				hhmakeParameterList += " -name ";
				hhmakeParameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				hhmakeParameterList += " -o ";
				hhmakeParameterList += experimentLocation;
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
	is.open(jsonFileName, ios::binary);

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
				hhsearchParameterList += tempValue;
			} else if (tempKey.compare("-d") == 0) {
				hhsearchParameterList += " -d ";
				hhsearchParameterList += databaseLocation;
				hhsearchParameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				hhsearchParameterList += " -o ";
				hhsearchParameterList += experimentLocation;
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
void HHSearch64::readFastaFile(string fastaFile) {
	ifstream ifs(fastaFile.c_str(), ios::in);
	if (ifs.is_open()) {
		getline(ifs, proteinName);
		getline(ifs, aminoAcids);
		ifs.close();
	} else {
		cout << "fasta file is unable to open" << endl;
	}

}

void HHSearch64::executeAlignment() {
	jsonParser();
	setHHSearchLibrary();
	readFastaFile(fastaFilename);
	runAlignHits();
	runHHMake();
	runHHSearch();
}
