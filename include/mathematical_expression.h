//
// Created by Liming on 2023/6/19.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H
#define MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H

#include "PrefixExpressionOperation.h"
#include "BracketsCalculationTwo.h"

#define VERSION "1.0.0-mathematical_expression-C++";

/**
 * 数学表达式解析计算库中的门户类，由该类获取到数学表达式计算库中的相关数据对象。
 *
 * The portal class in the mathematical expression analysis and calculation library, which obtains the relevant data objects in the mathematical expression calculation library.
 */
class mathematical_expression {
protected:
    ME::PrefixExpressionOperation prefixExpressionOperation;
    ME::BracketsCalculationTwo bracketsCalculation2;
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
};


#endif //MATHEMATICAL_EXPRESSION_CPP_MATHEMATICAL_EXPRESSION_H
