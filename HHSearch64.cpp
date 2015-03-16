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

void HHSearch64::jsonParser() const {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFileName, ios::binary);

	if (reader.parse(is, root)) {

		//read info from root
		string proteinName = root["proteinName"].asString();
		string aminoSeq = root["aminoSeq"].asString();
		string queryFileLocation = root["queryFileLocation"].asString();
		string alignmentToolLocation = root["alignmentToolLocation"].asString();
		string databaseLocation = root["databaseLocation"].asString();
		string experimentLocation = root["experimentLocation"].asString();
		string methodName = root["methodName"].asString();
		string a3m = root["-a3m"].asString();
		//cout << "proteinName " << proteinName << endl;
		//cout << "aminoSeq " << aminoSeq << endl;
		//cout << "queryFileLocation " << queryFileLocation << endl;
		//cout << "alignmentToolLocation " << alignmentToolLocation << endl;
		//cout << "databaseLocation " << databaseLocation << endl;
		//cout << "experimentLocation " << experimentLocation << endl;
		//cout << "methodName " << methodName << endl;

		string alignhitsParameterList = "perl ";
		alignhitsParameterList += alignmentToolLocation;
		alignhitsParameterList += "alignhits.pl ";
		alignhitsParameterList += experimentLocation;
		alignhitsParameterList += "query.blaNR ";
		alignhitsParameterList += "-a3m ";
		alignhitsParameterList += experimentLocation;
		alignhitsParameterList += a3m;

		Utility utility;
		char* cmd = utility.convertStringToCharArr(alignhitsParameterList);
		system(cmd);
		printf("%s\n", cmd);

		string hhmakeParameterList = alignmentToolLocation;
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

		cmd = utility.convertStringToCharArr(hhmakeParameterList);
		system(cmd);
		printf("%s\n", cmd);

		string hhsearchParameterList = alignmentToolLocation;
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

		cmd = utility.convertStringToCharArr(hhsearchParameterList);
		system(cmd);
		printf("%s\n", cmd);

	}

	is.close();
}

void HHSearch64::print() const {
	cout << "This is the derived HHSearch64 class";
}
