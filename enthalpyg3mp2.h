#ifndef _ENTHALPYG3MP2_H_
#define _ENTHALPYG3MP2_H_
#include "enthalpyinputdata.h"

/* **************************************************************************** */
class EnthalpyG3MP2 {
/* **************************************************************************** */
public:
/* **************************************************************************** */
        //Cálculo de la energía de atomización a 0 K
        double DeltaH_Elements(int atn);
        double SumDeltaH_a0k(EnthalpyInputData &input);
    
        //Cálculo de la entalpia de formación a 0 K
        double DeltaH_ElementsExperimental(int atn);
        double SumDeltaH_f0k(EnthalpyInputData &input);
        double HeatFormation_kJtokcal(EnthalpyInputData &input);

        //Incremento de la entalpía al pasar de 0 K a 298 K
        double DeltaDeltaH(EnthalpyInputData &input);

        //Cálculo de entalpia de formación a 298 K
        double ExperimentalEnthalpyElements(int atn);
        double DeltaDeltaH_Elements(EnthalpyInputData &input);
        double DeltaH_f298k(EnthalpyInputData &input);
        double DeltaH_f298k_kcal(EnthalpyInputData &input);

        //Correciones por termodinámica estadística
        double TSCorrection(EnthalpyInputData &input);
        double TSCorrectionResult(EnthalpyInputData &input);
        double EnthalpyTS(EnthalpyInputData &input);
        double EnthalpyTS_kcal(EnthalpyInputData &input);

        //Resultado
        double PrintResult(EnthalpyInputData &input);

/* **************************************************************************** */
protected:
/* **************************************************************************** */
/* **************************************************************************** */
};
/* **************************************************************************** */

#endif /* :ENTHALPYG3MP2_H_ */

