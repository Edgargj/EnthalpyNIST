#include "enthalpyinputdata.h"


void EnthalpyInputData::ReadData(string fname){
	

	ifstream filein(fname);

	filein >> method;
	
	cout << setprecision(8);

	filein >> atomic_species;

	filein >> energy;

	filein >> enthalpy;

	atomic_number.resize(atomic_species);
	number_atoms.resize(atomic_species);

	for (int i=0; i<atomic_species; ++i){

		filein >> atomic_number[i];
		filein >> number_atoms[i];
	}

	filein >> molecule_linearity;

	filein >> method_N_RR_HO;

	filein >> vibrational_modes;

	
	vibrational_freqencies.resize(vibrational_modes);	
	for (size_t i=0; i<vibrational_freqencies.size(); ++i){

		filein >> vibrational_freqencies[i];
	}

	filein.close();


}
