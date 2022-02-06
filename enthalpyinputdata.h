#ifndef _ENTHALPYINPUTDATA_H_
#define _ENTHALPYINPUTDATA_H_
//Esta clase lee archivos linea por linea
//using namespace std;

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>

using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::endl;
using std::ifstream;
using std::setprecision; 

/***************************************************************************************/ 
class EnthalpyInputData{
/***************************************************************************************/ 
public:
	string filename;
	string method;
	int atomic_species;
	long double energy;
	long double enthalpy;
	vector <int> atomic_number;
	vector <int> number_atoms;
	int molecule_linearity;
	int method_N_RR_HO;
	int vibrational_modes;
	vector <double> vibrational_freqencies;
/***************************************************************************************/ 
        void ReadData(string fname);
/***************************************************************************************/
};
#endif
//_ENTHALPYINPUTDATA_H_

