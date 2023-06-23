//
// Created by zhao on 2023/6/23.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H

#include "BracketsCalculationTwo.h"

namespace ME {

    /**
     * 累加计算公式解析组件，支持使用未知形参，以及其区间作为公式进行累加加过的计算，例如传入公式 “n [0, 10, 2] (1 + n * n)” 就是 (1 + 0 * 0) + (1 + 2 * 2) + ... + (1 + 10 * 10)
     * <p>
     * The cumulative calculation formula analysis component supports the use of unknown formal parameters and their intervals as formulas for cumulative calculation. For example, the formula "n [0, 10, 2] (1+n * n)" passed in is (1+0 * 0)+(1+2 * 2)+...+(1+10 * 10)
     *
     * @author zhao
     */
    class CumulativeCalculation : public BracketsCalculationTwo {
    public:
        string formatStr(std::string basicString) override;

        void check(std::string string) override;

        string getName() override;

        CalculationNumberResults calculation(std::string Formula, bool formatRequired) override;
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H
