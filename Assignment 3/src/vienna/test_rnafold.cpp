
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>

//include external libs
extern "C" 
{
    #include "fold.h"
}

#include "../accuracy/accuracy.h"

using namespace std;


int main()
{

	// chrono typedefs

	typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;


	// read in the testing set
	while (cin.good())
	{
		string id, rna, sstruct;
		cin >> id >> rna >> sstruct;
		// a structure string is used to get the predicted structure from RNAfold
		char *structure = new char[rna.size()+1];
		// fold that rna!
		Clock::time_point t0 = Clock::now();
		float fe = fold(rna.c_str(), structure);
		Clock::time_point t1 = Clock::now();

		milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);

		float fscore = calc_f1score(sstruct, string(structure));

		delete[] structure;

		//output
		cout << id << '\t' << ms.count() << '\t' << rna.size() << '\t' << fscore << endl;
		
		cin >> ws;
	}
	return 0;
}
