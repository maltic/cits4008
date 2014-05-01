
#include <iostream>
#include <string>

//include external libs
extern "C" 
{
    #include "MEA.h"
}

using namespace std;


int main()
{
	// read in the testing set
	while (cin.good())
	{
		string id, rna, sstruct;
		cin >> id >> rna >> sstruct;
		// a structure string is used to get the predicted structure from rnafold
		char *structure = new char[rna.size()+1];
		// fold that rna!
		float fe = fold(rna.c_str(), structure);
		//output
		cout << id << '\t' << fe << '\t' << structure << endl;
	}
	return 0;
}
