#include <cstdlib>
#include <iomanip>
#include <math.h>
#include <iostream>
#include <enthalpyinputdata.h>
#include "enthalpyg3.h"
#include "methodtype.h"

using std::cout;

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaH_Elements(int atn){

        static const double Elements0K[]={ 0.0, -0.5010030, 0.0, 0.0, 0.0, 0.0, -37.8277170, 0.0, 
                -75.0309910, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


        return Elements0K[atn];
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::SumDeltaH_a0k(EnthalpyInputData &input){

	double DeltaH_a0k = 0.0;
	double DeltaH_aElements = 0.0;
	double DeltaE_0kmolecule = input.energy;
	double antemp, natmp;
	const double htokj = 2625.4997480;

	for(int i =0;  i<input.atomic_species; i++){

		antemp = DeltaH_Elements(input.atomic_number[i]);
		natmp = input.number_atoms[i];
		DeltaH_aElements += antemp * natmp;
		DeltaH_a0k = (DeltaH_aElements - DeltaE_0kmolecule) * htokj;


	}	
	return DeltaH_a0k;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaH_ElementsExperimental(int atn){

        static const double g30K[]={ 0.0, 216.03500, 0.0, 157.80000, 317.10000, 569.90000, 711.185, 470.82000, 
		246.7900, 77.40000, 0.0, 107.60000, 146.50000, 327.30000, 452.30000, 315.60000, 274.73500, 119.60000, 
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


        return g30K[atn];
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::SumDeltaH_f0k(EnthalpyInputData &input){

	double DeltaH_0k = 0.0;
	double DeltaH_f0k = 0.0;
	double antmp, natmp;

	for(int i =0;  i<input.atomic_species; i++){

		antmp = DeltaH_ElementsExperimental(input.atomic_number[i]);
		natmp = input.number_atoms[i];
		DeltaH_0k += antmp * natmp;
		DeltaH_f0k = DeltaH_0k - SumDeltaH_a0k(input);


	}
	return DeltaH_f0k;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::HeatFormation_kJtokcal(EnthalpyInputData &input){

	double kcal = 0.0;
	double kJtokcal = 0.00023884589662750;

	kcal = (SumDeltaH_f0k(input) * kJtokcal) * 1000;

	return kcal;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaDeltaH(EnthalpyInputData &input){

	double G3_energy0k = input.energy;
	double G3_enthalpy298k = input.enthalpy;
	double DeltaDeltaH_molecule = 0.0;
	const double htokj = 2625.4997480;

	DeltaDeltaH_molecule = (G3_enthalpy298k - G3_energy0k) * htokj; 

	return DeltaDeltaH_molecule;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::ExperimentalEnthalpyElements(int atn){

        static const double g30K[]={ 0.0, 8.46700/2, 0.0, 4.62800, 1.95000, 1.21300, 1.05100, 8.67000/2, 8.68300/2, 8.82000/2,
                0.0, 6.44000, 5.00000, 4.57700, 3.21700, 5.36000, 4.41200, 9.17600, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


        return g30K[atn];
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaDeltaH_Elements(EnthalpyInputData &input){

	double DeltaDeltaH_elements = 0.0;
	double antmp, natmp;

	for(int i=0; i<input.atomic_species; i++){

		antmp = ExperimentalEnthalpyElements(input.atomic_number[i]);
		natmp = input.number_atoms[i];
		DeltaDeltaH_elements += natmp * antmp;

	}
	return DeltaDeltaH_elements;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaH_f298k(EnthalpyInputData &input){

	double DeltaH_f298k = 0.0;

	DeltaH_f298k = SumDeltaH_f0k(input) + DeltaDeltaH(input) - DeltaDeltaH_Elements(input);

	return DeltaH_f298k;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::DeltaH_f298k_kcal(EnthalpyInputData &input){

	double kcal = 0.0;
	double kJtokcal = 0.00023884589662750;

	kcal = (DeltaH_f298k(input) * kJtokcal) * 1000;

	return kcal;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::TSCorrection(EnthalpyInputData &input){

	const double c = 2.99792458E8;
	const double h = 6.62606957E-34;
	const double NA = 6.02214129E23;
	const double k = 1.380658E-23;
	const double T = 298.15;
	const double R = 8.314510;
	double fscale = 0.89290;
	double vib = 0.0;
	double num = 0.0;
	double factor = 0.0;	
	double den = 0.0;
	double rot = 0.0;
	double trans = 0.0;
	double pv = 0.0;
	double deltht = 0.0;

	for (size_t i=0; i<input.vibrational_freqencies.size(); i++){

		if (input.method_N_RR_HO == 0 && input.vibrational_freqencies[i]*fscale < 260){
			vib = vib + (0.5*R*T);
		
		} else{ num = input.vibrational_freqencies[i]*fscale*100.00*c*NA*h;
			factor = (input.vibrational_freqencies[i]*fscale*100.00*c*h)/(k*T);
			den = exp(factor)-1;
			vib = vib + (num/den);
		}	
	}
	if (input.molecule_linearity == 1){
		rot = R*T;
	} else { rot = 1.5*R*T; 
	}		
	trans = 1.5*R*T;
	pv = R*T;
	deltht = vib + rot + trans + pv;
	
	return deltht;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::TSCorrectionResult(EnthalpyInputData &input){

	double Sum = 0.0;

	Sum =  (TSCorrection(input)) / 1000; 

	return Sum;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::EnthalpyTS(EnthalpyInputData &input){

	double TSDeltaH_f298 = 0.0;

	TSDeltaH_f298 = SumDeltaH_f0k(input) + TSCorrectionResult(input) - (DeltaDeltaH_Elements(input));

	return TSDeltaH_f298;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::EnthalpyTS_kcal(EnthalpyInputData &input){

	double kcal = 0.0;
	double kJtokcal = 0.00023884589662750;

	kcal = (EnthalpyTS(input) * kJtokcal) * 1000;

	return kcal;
}

/* ***********************************************G3*********************************************** */

double EnthalpyG3::EnthalpyResult(EnthalpyInputData &input){

	MethodType MethodNorRRHO;

	cout << "                                                                                                   " << endl;
        cout << "===================================================================================================" << endl;
        cout << "                      New calculation of molecular enthalpies of formation                         " << endl;
        cout << "                                                                                                   " << endl;
        cout << "              Enthalpies of formation of gaseous atoms at 0 K and thermal corrections              " << endl;
        cout << "                       for elements in their standard state at 298.16 K from:                      " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       NIST-JANAF Thermochemical Tables J. Physics Chem. Data Monograph 9, 1998, 1-1951.           " << endl;
        cout << "===================================================================================================" << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "Heats of formation: " << endl;
        cout << "0K          " << std::fixed << std::setprecision(2) << SumDeltaH_f0k(input) << " kJ mol-1" << endl;
        cout << "0K          " << HeatFormation_kJtokcal(input) << " kcal mol-1" << endl;
        cout << "                                                                                                   " << endl;
        cout << MethodNorRRHO.Method_Type(input) << endl;
        cout << "298K        " << EnthalpyTS(input) << " kJ mol-1" << endl;
        cout << "298K        " << EnthalpyTS_kcal(input) << " kcal mol-1" << endl;
        cout << "                                                                                                   " << endl;
        cout << "Using G3: " << endl;
        cout << "298K        " << DeltaH_f298k(input) << " kJ mol-1" << endl;
        cout << "298K        " << DeltaH_f298k_kcal(input) << " kcal mol-1" << endl;
        cout << "                                                                                                   " << endl;
        cout << "===================================================================================================" << endl;	

	return 0.0e0;
}

/* ***********************************************G3*********************************************** */

