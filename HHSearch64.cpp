/*
 * HHSearch64.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: Chao
 */

#include "HHSearch64.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <string>

HHSearch64::HHSearch64(char* rootName) :
		AlignmentTool(rootName) {
	// TODO Auto-generated constructor stub
	fastaFilename = rootName;
	fastaFilename += ".fasta";

}

HHSearch64::~HHSearch64() {
	// TODO Auto-generated destructor stub
}
void HHSearch64::addQueryInfo2a3m() {
	//make a copy of query.a3m into queryOriginal.a3m
	char pcLine[2000];
	FILE* fptrOriginal, *fptr;
	string fileLocation(experimentLocation);
	fileLocation += rootName;
	fileLocation += "/query.a3m";
	fptr = fopen((char*) fileLocation.c_str(), "r");
	string fileOriginalLocation(experimentLocation);
	fileOriginalLocation += rootName;
	fileOriginalLocation += "/queryOriginal.a3m";
	fptrOriginal = fopen((char*) fileOriginalLocation.c_str(), "w");

	while (1) {
		fgets(pcLine, 2000, fptr);
		if(feof(fptr)){
			break;
		}
		fprintf(fptrOriginal, "%s", pcLine);
	}
	fclose(fptrOriginal);
	fclose(fptr);

	//add query info to a3m
	fileOriginalLocation = "";
	fileOriginalLocation += experimentLocation;
	fileOriginalLocation += rootName;
	fileOriginalLocation += "/queryOriginal.a3m";
	fptrOriginal = fopen((char*) fileOriginalLocation.c_str(), "r");

	fileLocation = "";
	fileLocation += experimentLocation;
	fileLocation += rootName;
	fileLocation += "/query.a3m";
	fptr = fopen((char*) fileLocation.c_str(), "w");

	string fastaFilePosition(fastaFileLocation);
	fastaFilePosition += fastaFilename;
	FILE *fptr_fasta = fopen((char*) fastaFilePosition.c_str(), "r");
	fgets(pcLine, 2000, fptr_fasta);
	string proteinName(pcLine);
	fprintf(fptr, ">pdb|%s\n", (char*)proteinName.substr(1,5).c_str());
	fgets(pcLine, 2000, fptr_fasta);
	fprintf(fptr, "%s\n", pcLine);
	fclose(fptr_fasta);
	while (1) {
		fgets(pcLine, 2000, fptrOriginal);
		if(feof(fptrOriginal)){
			break;
		}
		fprintf(fptr, "%s", pcLine);
	}
	fclose(fptr);
	fclose(fptrOriginal);
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

		//cout<<fastaFilename<<endl;
		alignmentToolLocation = root["alignmentToolLocation"].asString();
		databaseLocation = root["databaseLocation"].asString();
		experimentLocation = root["experimentLocation"].asString();
		fastaFileLocation = root["fastaFileLocation"].asString();
		_a3m = root["-a3m"].asString();
		//cout<<"asdfasdfadsf"<<alignmentToolLocation<<databaseLocation<<endl;
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
	alignhitsParameterList += "query.blaNR ";
	alignhitsParameterList += "-a3m ";
	alignhitsParameterList += experimentLocation;
	alignhitsParameterList += "/";
	alignhitsParameterList += rootName;
	alignhitsParameterList += "/";
	alignhitsParameterList += _a3m;

	Utility utility;
	char* cmd = utility.convertStringToCharArr(alignhitsParameterList);
	system(cmd);
	printf("--------1. runAlignHits command is:------------\n%s\n", cmd);
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
	printf("----------2. runHHMake command is:--------- \n%s\n", cmd);
}

void HHSearch64::runHHSearch(string const parameterSetting) {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open(jsonFilename.c_str(), ios::binary);

	if (reader.parse(is, root)) {
		hhsearchParameterList = alignmentToolLocation;
		hhsearchParameterList += "hhsearch ";
		//"%shhsearch -i %squery.hhm -d %scal.hhm -cal -o %squery.hhrNR",
		for (Json::Value::iterator it = root[parameterSetting].begin();
				it != root[parameterSetting].end(); it++)

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
	printf("-----------3. runHHSearch command is:----------\n%s\n", cmd);
}

void HHSearch64::executeAlignment(string configFile) {
	setJsonFilename(configFile);
	jsonParser();

	runAlignHits();
	addQueryInfo2a3m();
	runHHMake();
	runHHSearch("HHSearchNRParameterSetting");
	runHHSearch("HHSearchParameterSetting");

}
