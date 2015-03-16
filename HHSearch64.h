/*
 * HHSearch64.h
 *
 *  Created on: Mar 13, 2015
 *      Author: Chao
 */

#ifndef HHSEARCH64_H_
#define HHSEARCH64_H_
#include <assert.h>
#include <iostream>
#include <fstream>

#include "AlignmentTool.h"
#include "json/json.h"
#include "Utility.h"
class HHSearch64: public AlignmentTool {
public:
	HHSearch64(char*);
	virtual void jsonParser() const;
	virtual void print() const;
	virtual ~HHSearch64();
};

#endif /* HHSEARCH64_H_ */
