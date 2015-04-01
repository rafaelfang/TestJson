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

	int numOfExp = 0;
	if (argc == 0 || argc == 1) {
		cout << "not enough arguments provided!" << endl;
		exit(-1);
	}
	for (numOfExp = 1; numOfExp <= (argc - 1) / 2; numOfExp++) {
		string methodChose(argv[2*numOfExp]);
		if (methodChose.compare("blast") == 0) {
			Blast blast(argv[2*numOfExp-1]);
			blast.executeAlignment();
		} else if (methodChose.compare("hhsearch") == 0) {
			HHSearch64 hhsearch(argv[2*numOfExp-1]);
			hhsearch.executeAlignment();
		}
	}

}

