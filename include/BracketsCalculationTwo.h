//
// Created by Liming on 2023/6/20.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATIONTWO_H
#define MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATIONTWO_H

#include "regex"
#include "BracketsCalculation.h"

namespace ME {

    /**
     * 将一个带有嵌套括号的表达式数值结果计算，能够识别嵌套括号的就按优先级，是括号表达式计算的实现类
     * <p>
     * Compute the numerical results of an expression with nested parentheses. Those that can recognize nested parentheses are prioritized. They are the implementation classes of the calculation of parenthesis expressions
     *
     * @author zhao
     */
    class BracketsCalculationTwo : public BracketsCalculation {

    public:
        string formatStr(std::string string) override;

        void check(std::string string) override;

        ME::CalculationNumberResults operator>>(std::string &format);

        ME::CalculationNumberResults operator<<(std::string &format);

        string getName() override;

        CalculationNumberResults calculation(std::string Formula, bool formatRequired) override;
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_BRACKETSCALCULATIONTWO_H
