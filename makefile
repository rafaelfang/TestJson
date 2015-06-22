mufoldAlignment: runner.o jsoncpp.o AlignmentTool.o CNFSearch.o Blast.o HHSearch64.o Utility.o
	g++ runner.o jsoncpp.o AlignmentTool.o CNFSearch.o Blast.o HHSearch64.o Utility.o -o mufoldAlignment

runner.o: runner.cpp
	g++ -c runner.cpp	

jsoncpp.o: jsoncpp.cpp
	g++ -c jsoncpp.cpp
AlignmentTool.o: AlignmentTool.cpp
	g++ -c AlignmentTool.cpp
Blast.o: Blast.cpp
	g++ -c Blast.cpp
HHSearch64.o : HHSearch64.cpp
	g++ -c HHSearch64.cpp
CNFSearch.o:CNFSearch.cpp
	g++ -c CNFSearch.cpp
Utility.o: Utility.cpp
	g++ -c Utility.cpp


clean:
	rm *.o mufoldAlignment