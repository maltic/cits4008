
#include <iostream>
#include <string>

//include external libs
extern "C" 
{
    #include "cofold.h"
}

using namespace std;


int main()
{
	// read in the testing set
	while (cin.good())
	{
		string id, rna, sstruct;
		cin >> id >> rna >> sstruct;
		// a structure string is used to get the predicted structure from cofold
		char *structure = new char[rna.size()+1];
		// cofold that rna!
		float fe = cofold(rna.c_str(), structure);
		//output
		cout << id << '\t' << fe << '\t' << structure << endl;
	}
	return 0;
}
