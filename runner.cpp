#include <cstdlib>
#include <iostream>
#include <string>

#include "Blast.h"
#include "CNFSearch.h"
#include "HHSearch64.h"

using namespace std;

int main(int argc, char* argv[]) {


	if (argc < 3) {
		cout << "not enough arguments provided!" << endl;
		exit(-1);
	}

	string methodChose(argv[1]);
	if (methodChose.compare("-blast") == 0) {
		Blast blast(argv[2]);
		blast.executeAlignment("configBlastNRC.json");
		blast.executeAlignment("configBlastNRR.json");
		blast.executeAlignment("configBlastPDB.json");
	} else if (methodChose.compare("-hhsearch") == 0) {
		Blast blast(argv[2]);
		blast.executeAlignment("configBlastNRC.json");
		blast.executeAlignment("configBlastNRR.json");
		blast.executeAlignment("configBlastPDB.json");
		HHSearch64 hhsearch(argv[2]);
		hhsearch.executeAlignment("configHHSearchhhm.json");
		hhsearch.executeAlignment("configHHSearchhhmNR.json");
	}else if(methodChose.compare("-cnfsearch")==0){
		CNFSearch cnfSearch(argv[2]);
		cnfSearch.executeAlignment("configCNFSearch.json");
	}

}

