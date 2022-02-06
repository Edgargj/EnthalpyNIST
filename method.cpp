#include <cstdlib>
#include <iostream>
using std::cout;

#include "method.h"
#include "enthalpyg3.h"
#include "enthalpyg4.h"
#include "enthalpyg3mp2.h"
#include "enthalpycbsqb3.h"
#include "enthalpycbsapno.h"

double Method::ComputeEnthalpy(EnthalpyInputData &input) {
   
   if (input.method==string("G4")) {
      EnthalpyG4 g4;
	return g4.EnthalpyResult(input);
   } else if ( input.method==string("G3")) {
      EnthalpyG3 g3;
      return g3.EnthalpyResult(input);
   } else if (input.method==string("G3MP2")){
      EnthalpyG3MP2 g3mp2;
      return g3mp2.EnthalpyResult(input);
   } else if (input.method==string("CBS-QB3")){
      EnthalpyCBSQB3 cbsqb3;
      return cbsqb3.EnthalpyResult(input);
   } else if (input.method==string("CBS-APNO")){
      EnthalpyCBSAPNO cbsapno;
      return cbsapno.EnthalpyResult(input);
   }
   return 0.0e0;
}

