#include <cstdlib>
#include <iostream>
#include <methodtype.h>
#include <enthalpyinputdata.h>

using std::cout;

string MethodType::Method_Type(EnthalpyInputData &input){

	string mn = "Using Nicolaides method: ";
	string mrrho = "Using RR and HO method: ";

		if (input.method_N_RR_HO == 0){
			return mn;
		}
			else if(input.method_N_RR_HO == 1){
			return mrrho;
	}
	return 0;
}
