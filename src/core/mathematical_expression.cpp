//
// Created by Liming on 2023/6/20.
//
#include "mathematical_expression.h"

ME::PrefixExpressionOperation mathematical_expression::getPrefixExpressionOperation() {
    return mathematical_expression::prefixExpressionOperation;
}

ME::BracketsCalculationTwo mathematical_expression::getBracketsCalculation2() {
    return mathematical_expression::bracketsCalculation2;
}

ME::BooleanCalculationTwo mathematical_expression::getBooleanCalculation2() {
    return mathematical_expression::booleanCalculation2;
}

ME::FunctionFormulaCalculation mathematical_expression::getFunctionFormulaCalculation() {
    return mathematical_expression::functionFormulaCalculation;
}

ME::CumulativeCalculation mathematical_expression::getCumulativeCalculation() {
    return mathematical_expression::cumulativeCalculation;
}
