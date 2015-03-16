/*
 * Alignment.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: Chao
 */
#include "AlignmentTool.h"

#include <iostream>
using namespace std;

AlignmentTool::AlignmentTool(char* myJsonFileName) {
	setJsonFileName(myJsonFileName);
}

void AlignmentTool::print() const {
	cout << "This is the base class: Alignment";
}

AlignmentTool::~AlignmentTool() {
	// TODO Auto-generated destructor stub
}

char* AlignmentTool::getJsonFileName() const {
	return jsonFileName;
}

void AlignmentTool::setJsonFileName(char* jsonFileName) {
	this->jsonFileName = jsonFileName;
}
