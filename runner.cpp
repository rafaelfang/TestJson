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

	if (argc < 3) {
		cout << "not enough arguments provided!" << endl;
		exit(-1);
	}

	string methodChose(argv[1]);
	if (methodChose.compare("-blast") == 0) {
		Blast blast(argv[2]);
		blast.executeAlignment("configBlast1.json");
		blast.executeAlignment("configBlast2.json");
	} else if (methodChose.compare("-hhsearch") == 0) {
		Blast blast(argv[2]);
		blast.executeAlignment("configBlast1.json");
		blast.executeAlignment("configBlast2.json");
		HHSearch64 hhsearch(argv[2]);
		hhsearch.executeAlignment("configHHSearch1.json");
		hhsearch.executeAlignment("configHHSearch2.json");
	}

}

