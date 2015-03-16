/*
 * Utility.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: Chao
 */

#include "Utility.h"

Utility::Utility() {
	// TODO Auto-generated constructor stub

}
char* Utility::convertStringToCharArr(string s) {
	int length = s.length();
	char* ptr = new char[length + 1];
	s.copy(ptr, length, 0);
	ptr[length] = '\0';
	return ptr;
}
Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

