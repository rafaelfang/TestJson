/*
 * Blast.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Chao
 */
#include <iostream>
#include "Blast.h"
using namespace std;

Blast::Blast(char* jsonFileName) :
		AlignmentTool(jsonFileName) {

}
Blast::~Blast() {

}

void Blast::readFastaFile(string fastaFile) {
	ifstream ifs(fastaFile.c_str(), ios::in);
	if (ifs.is_open()) {
		getline(ifs, proteinName);
		//cout<<proteinName<<endl;;
		getline(ifs, aminoAcids);
		//cout<<aminoAcids<<endl;;
		ifs.close();
	} else {
		cout << "fasta file is unable to open" << endl;
	}

}
void Blast::jsonParser() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFileName, ios::binary);

	if (reader.parse(is, root)) {

		//read info from root
		fastaFilename = root["fastaFilename"].asString();
		alignmentToolLocation = root["alignmentToolLocation"].asString();
		databaseLocation = root["databaseLocation"].asString();
		experimentLocation = root["experimentLocation"].asString();

		parameterList = alignmentToolLocation;
		parameterList += "blastpgp";

		for (Json::Value::iterator it = root["parameterSetting"].begin();
				it != root["parameterSetting"].end(); it++)

				{

			Json::Value key = it.key();

			Json::Value value = (*it);

			string tempKey = key.asString();

			string tempValue = value.asString();

			if (tempKey.compare("-i") == 0) {
				parameterList += " -i ";
				parameterList += experimentLocation;
				parameterList += fastaFilename;
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

	}

	is.close();

}
void Blast::executeAlignment() {
	jsonParser();
	readFastaFile(fastaFilename);
	Utility utility;
	char* cmd = utility.convertStringToCharArr(parameterList);
	system(cmd);
	printf("%s\n", cmd);
}

