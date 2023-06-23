//
// Created by zhao on 2023/6/22.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATIONTWO_H
#define MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATIONTWO_H

#include "BooleanCalculation.h"

namespace ME {
    /**
     * 计算一个布尔返回值的表达式，该组件针对两个表达式或数值之间的比较来计算结果数值，用于比较表达式是否成立
     * <p>
     * An expression that calculates a Boolean return value. This component calculates the result value for the comparison between two expressions or values, and is used to compare whether the expression is valid
     *
     * @author zhao
     */
    class BooleanCalculationTwo : public BooleanCalculation {
    public:

        string formatStr(std::string string) override;

        void check(std::string string) override;

        string getName() override;

        CalculationBooleanResults operator>>(string &format) override;

        CalculationBooleanResults operator<<(string &format) override;

        CalculationBooleanResults calculation(std::string Formula, bool formatRequired) override;
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATIONTWO_H
