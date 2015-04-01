#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include "AlignmentTool.h"
#include "json/json.h"
#include "Blast.h"
#include "HHSearch64.h"
using namespace std;

int main(int argc, char* argv[]) {
	//before the next step, this command is a must, you need to go to linux shell to
	//run the following command:
	//export HHLIB=<install_dir>/lib/hh
	//export HHLIB=~lihongb/Tools/hhsearch64/lib/hh
	Blast blast1(argv[1]);
	blast1.executeAlignment();
	Blast blast2(argv[2]);
	blast2.executeAlignment();
	HHSearch64 hhsearch1(argv[3]);
	hhsearch1.executeAlignment();
	HHSearch64 hhsearch2(argv[4]);
	hhsearch2.executeAlignment();
	//AlignmentTool* alignmentPtr[4];
	//alignmentPtr[0] = &blast1;
	//alignmentPtr[1] = &blast2;
	//alignmentPtr[2] = &hhsearch1;
	//alignmentPtr[3] = &hhsearch2;
	//int i = 0;
	//for (i = 0; i < 4; i++) {
	//	alignmentPtr[i]->jsonParser();
	//}

}

