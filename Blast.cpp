/*
 * Blast.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Chao
 */
#include <iostream>
#include "Blast.h"
using namespace std;

Blast::Blast(char* jsonFileName):AlignmentTool(jsonFileName)  {

}
Blast::~Blast(){

}
void Blast::jsonParser() const {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFileName, ios::binary);
	string returnString;
	if (reader.parse(is, root)) {

		//read info from root
		string proteinName = root["proteinName"].asString();
		string aminoSeq = root["aminoSeq"].asString();
		string queryFileLocation = root["queryFileLocation"].asString();
		string alignmentToolLocation = root["alignmentToolLocation"].asString();
		string databaseLocation = root["databaseLocation"].asString();
		string experimentLocation = root["experimentLocation"].asString();
		string methodName = root["methodName"].asString();

		//cout << "proteinName " << proteinName << endl;
		//cout << "aminoSeq " << aminoSeq << endl;
		//cout << "queryFileLocation " << queryFileLocation << endl;
		//cout << "alignmentToolLocation " << alignmentToolLocation << endl;
		//cout << "databaseLocation " << databaseLocation << endl;
		//cout << "experimentLocation " << experimentLocation << endl;
		//cout << "toolName " << toolName << endl;

		string parameterList = alignmentToolLocation;
		parameterList += methodName;

		for (Json::Value::iterator it = root["parameterSetting"].begin();
				it != root["parameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-i") == 0) {
				parameterList += " -i ";
				parameterList += queryFileLocation;
				parameterList += tempValue;
			} else if (tempKey.compare("-o") == 0) {
				parameterList += " -o ";
				parameterList += experimentLocation;
				parameterList += tempValue;
			} else if (tempKey.compare("-R") == 0) {
				parameterList += " -R ";
				parameterList += experimentLocation;
				parameterList += tempValue;
			} else if (tempKey.compare("-Q") == 0) {
				parameterList += " -Q ";
				parameterList += experimentLocation;
				parameterList += tempValue;
			} else if (tempKey.compare("-d") == 0) {
				parameterList += " -d ";
				parameterList += databaseLocation;
				parameterList += tempValue;
			} else if (tempKey.compare("-e") == 0) {
				parameterList += " -e ";
				parameterList += tempValue;
			} else if (tempKey.compare("-v") == 0) {
				parameterList += " -v ";
				parameterList += tempValue;
			} else if (tempKey.compare("-b") == 0) {
				parameterList += " -b ";
				parameterList += tempValue;
			} else if (tempKey.compare("-j") == 0) {
				parameterList += " -j ";
				parameterList += tempValue;
			} else if (tempKey.compare("-h") == 0) {
				parameterList += " -h ";
				parameterList += tempValue;
			} else if (tempKey.compare("-C") == 0) {
				parameterList += " -C ";
				parameterList += experimentLocation;
				parameterList += tempValue;
			}
		}
		returnString += parameterList;

	}

	is.close();
	Utility utility;
	char* cmd = utility.convertStringToCharArr(returnString);
	system(cmd);
	printf("%s\n", cmd);
}
void Blast::print() const {
	cout << "This is the derived Blast class";
}

