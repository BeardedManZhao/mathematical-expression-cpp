//
// Created by Liming on 2023/6/20.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATION_H

#include <regex>
#include "PrefixExpressionOperation.h"
#include "ConstantRegion.h"

namespace ME {

    /**
     * 括号解析算法计算一个公式的计算组件的父类，其中的计算具体实现是一个抽象，等待实现
     * <p>
     * The bracket parsing algorithm calculates the parent class of the calculation component of a formula, in which the specific implementation of the calculation is an abstract, waiting to be implemented
     *
     * @author zhao
     */
    class BracketsCalculation : public Calculation {

    public:
        string formatStr(std::string string) override;

        void check(std::string string) override;

        string getName() override;

        virtual
        /**
         * 计算一个数学表达式，并将计算细节与计算结果存储到数值结果集中。
         * <p>
         * Compute a mathematical expression and store the calculation details and results in the numerical result set.
         *
         * @param Formula        被计算的表达式，要求返回值是一个数值。
         *                       <p>
         *                       The returned value of the evaluated expression is required to be a numeric value.
         * @param formatRequired 是否需要被格式化，用于确保公式格式正确。
         *                       <p>
         *                       Whether it needs to be formatted to ensure that the formula format is correct.
         * @return 数值结果集对象，其中保存着每一步的操作数据，以及最终结果数值
         * <p>
         * Numerical result set object, which stores the operation data of each step and the final result value
         */
        CalculationNumberResults calculation(std::string Formula, bool formatRequired) = 0;

    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATION_H
