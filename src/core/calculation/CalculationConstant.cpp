//
// Created by zhao on 2023/6/23.
//

#include "CalculationConstant.h"

static ME::BracketsCalculationTwo bracketsCalculationTwo;

struct ME::FunctionFormulaCalculationTwo formulaCalculationTwo;

ME::BracketsCalculationTwo ME::CalculationConstant::getBracketsCalculationTwo() {
    return bracketsCalculationTwo;
}

ME::FunctionFormulaCalculationTwo ME::CalculationConstant::getFunctionFormulaCalculationTwo() {
    return formulaCalculationTwo;
}


