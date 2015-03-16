/*
 * Blast.h
 *
 *  Created on: Mar 10, 2015
 *      Author: Chao
 */

#ifndef BLAST_H_
#define BLAST_H_
#include <assert.h>
#include <iostream>
#include <fstream>

#include "AlignmentTool.h"
#include "json/json.h"
#include "Utility.h"
class Blast: public AlignmentTool {
public:
	//constructor
	Blast(char*);
	virtual void jsonParser() const;
	virtual void print() const;
	virtual ~Blast();

};

#endif /* BLAST_H_ */
