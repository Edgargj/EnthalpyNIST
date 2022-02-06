#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <optflag.h>
using std::cout;
using std::string;

/* *********************************************************************************** */
OptionFlags::OptionFlags(){
 	beging = false;
	end = false;
	save = false;
}

/* *********************************************************************************** */
void OptionFlags::getOptions(int &argc, char** &argv){

	if (argc == 3 && argv[2] == string ("-t")){
		cout << "entering Tajti" << endl;
	}

}


/* *********************************************************************************** */
