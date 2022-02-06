#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>
#include "enthalpyinputdata.h"
#include "optflag.h"
#include "method.h"
#include "methodtype.h"
#include "enthalpyg4.h"
#include "enthalpyg3mp2.h"
#include "enthalpycbsqb3.h"
#include "enthalpycbsapno.h"
using std::string;

int main (int argc, char *argv[])
{	
	string inputname=argv[1];

	//OptionFlags opt;
	//opt.getOptions(argc, argv);

	EnthalpyInputData datainput;
	datainput.ReadData(inputname);
	
	Method method;
	cout << method.ComputeEnthalpy(datainput) << endl;
	
	return 0;
}
