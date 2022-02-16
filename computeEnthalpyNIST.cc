#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <math.h>
#include "enthalpyinputdata.h"
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

	EnthalpyInputData datainput;
	datainput.ReadData(inputname);
	
	Method method;
	method.ComputeEnthalpy(datainput);
	
	return 0;
}
