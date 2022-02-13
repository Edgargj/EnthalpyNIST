# EnthalpyNIST

EnthalpyNIST is a program that calculates the enthalpies of formation (by the Gaussian09 G3, G3MP2, G4, CBS-APNO and CBS-QB3 method) of gaseous atoms at 0 K and thermal corrections for elements in their standard state at 298.15 K from: NIST-JANAF Thermochemical Tables J. Physics Chem. Data Monograph 9, 1998, 1-1951.

# Git instructions

You can obtain the source code of EnthalpyNIST as follows.
In your bash terminal type:

~~~~~~~~~~
$cd /local/path/to/EnthalpyNIST
$git clone https://github.com/Edgargj/EnthalpyNIST.git
~~~~~~~~~~

After this, git will transfer the source files to ```/local/path/to/EnthalpyNIST```

## Auxiliary programs/dependencies
The following dependencies are needed:

~~~~~~~~~~
g++ std=c++11 make
~~~~~~~~~~

## Installation
For installing the program, type:

~~~~~~~~~~
$cd /local/path/to/EnthalpyNIST
$make
~~~~~~~~~~

# Testing the program

How to test the program (or how it should be):

~~~~~~~~~~
$./computeEnthalpyNIST.x 4NBALa.txt

===================================================================================================
                      New calculation of molecular enthalpies of formation                         
                                                                                                   
              Enthalpies of formation of gaseous atoms at 0 K and thermal corrections              
                       for elements in their standard state at 298.15 K from:                      
                                                                                                   
       NIST-JANAF Thermochemical Tables J. Physics Chem. Data Monograph 9, 1998, 1-1951.           
===================================================================================================
                                                                                                   
                                                                                                   
                                                                                                   
Heats of formation: 
0K          -38.05 kJ mol-1
0K          -9.09 kcal mol-1
                                                                                                   
Using Nicolaides method: 
298K        -60.56 kJ mol-1
298K        -14.46 kcal mol-1
                                                                                                   
Using G4 Enthalpy: 
298K        -58.07 kJ mol-1
298K        -13.87 kcal mol-1
                                                                                                   
===================================================================================================
~~~~~~~~~~

