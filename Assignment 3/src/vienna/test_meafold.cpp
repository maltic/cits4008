
#include <iostream>
#include <string>
#include <chrono>

//include external libs
extern "C" 
{
    #include "fold.h"
    #include "part_func.h"
    #include "MEA.h"
    #include "data_structures.h"
    #include "params.h"
    #include "fold_vars.h"

}


using namespace std;


int main()
{

	// chrono typedefs

	typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    // gamma value to use in MEA
    // 1.0 is the vienna rna default and is backed up by research
    const float gamma = 1.0;

    model_detailsT md;
    set_model_details(&md);

    // these seems like magic numbers because they are
    // i basically ripped the default settings from RNAfold
    pf_paramT *params = get_boltzmann_factors(37.0, 1.0, md, 1.9);

    // cout << params->pf_scale << endl;


	// read in the testing set
	while (cin.good())
	{
		string id, rna, sstruct;
		cin >> id >> rna >> sstruct;
		// fold that rna!
		Clock::time_point t0 = Clock::now();

		// compute partition function
		double fe = pf_fold_par (rna.c_str(), NULL, params, 1, 0, 0);

	    char *ss = new char[rna.size()+1];
	    for (int i = 0; i < rna.size(); ++i)
	        ss[i] = '.';
	    ss[rna.size()] = '\0';
	    // get prob matrix and list
	    double *bppm = export_bppm();
	    plist *pl = NULL;
	    assign_plist_from_pr(&pl, bppm, rna.size(), 0.0);
	    // compute MEA structure
	    float score = MEA(pl, ss, gamma);


		Clock::time_point t1 = Clock::now();

		milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);


		//output
		cout << id << '\t' << ms.count() << '\t' << score << '\t' << ss << endl;
		
		cin >> ws;
	}
	return 0;
}
