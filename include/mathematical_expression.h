//
// Created by Liming on 2023/6/19.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H
#define MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H

#include "PrefixExpressionOperation.h"
#include "BracketsCalculationTwo.h"
#include "BooleanCalculationTwo.h"
#include "CumulativeCalculation.h"
#include "FunctionFormulaCalculation.h"

#define VERSION "1.0.1-mathematical_expression-C++";

/**
 * 数学表达式解析计算库中的门户类，由该类获取到数学表达式计算库中的相关数据对象。
 *
 * The portal class in the mathematical expression analysis and calculation library, which obtains the relevant data objects in the mathematical expression calculation library.
 */
class mathematical_expression {
protected:
    ME::PrefixExpressionOperation prefixExpressionOperation;
    ME::BracketsCalculationTwo bracketsCalculation2;
    ME::BooleanCalculationTwo booleanCalculation2;
    ME::CumulativeCalculation cumulativeCalculation;
    ME::FunctionFormulaCalculation functionFormulaCalculation;
public:

    /**
     *
     * @return 此库的版本信息。
     *
     * The version information of this library.
     */
    static string getVERSION() {
        return VERSION
    }

    /**
     *
     * @return 无括号表达式计算组件对象。
     *
     * An expression without parentheses evaluates a component object.
     */
    ME::PrefixExpressionOperation getPrefixExpressionOperation();

    /**
     *
     * @return 数学表达式计算组件，该组件能够解析并计算一个带有括号的表达式。
     *
     * Mathematical expression calculation component, which can parse and evaluate an expression with parentheses.
     */
    ME::BracketsCalculationTwo getBracketsCalculation2();

    /**
     *
     * @return 比较运算数学表达式计算组件，该组件能够解析并计算一个不等或等式是否成立。
     *
     * Compare the Computational mathematics expression calculation component, which can analyze and calculate whether an inequality or equality is true.
     */
    ME::BooleanCalculationTwo getBooleanCalculation2();

    /**
     *
     * @return 区间累加数学表达式解析计算组件，该组件能够实现按照一定等差的数列求和的方式进行公式的计算操作。
     *
     * Interval accumulation mathematical expression analysis and calculation component, which can perform formula calculation operations by summing a certain sequence of equal differences.
     */
    ME::CumulativeCalculation getCumulativeCalculation();

    /**
     *
     * @return 函数数学表达式计算组件，该组件能够解析一个引用了函数的表达式，能够有效的实现自定义计算函数的效果。
     *
     * Function mathematical expression calculation component, which can parse an expression that references a function and effectively achieve the effect of custom calculation functions.
     */
    ME::FunctionFormulaCalculation getFunctionFormulaCalculation();

};


#endif //MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H
