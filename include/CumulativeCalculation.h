//
// Created by zhao on 2023/6/23.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H

#include "BracketsCalculationTwo.h"

namespace ME {
    class CumulativeCalculation : public BracketsCalculationTwo {
    public:
        string formatStr(std::string basicString) override;

        void check(std::string string) override;

        string getName() override;

        CalculationNumberResults calculation(std::string Formula, bool formatRequired) override;
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_CUMULATIVECALCULATION_H
