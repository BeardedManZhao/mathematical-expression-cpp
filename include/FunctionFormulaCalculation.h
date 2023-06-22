//
// Created by zhao on 2023/6/22.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATION_H

#include "NumberCalculation.h"

namespace ME {
    class FunctionFormulaCalculation : public NumberCalculation {
    public:
        string formatStr(std::string string) override;

        void check(std::string string) override;

        CalculationNumberResults operator>>(std::string &format);

        CalculationNumberResults operator<<(std::string &format);

        string getName() override;

        CalculationNumberResults calculation(std::string Formula, bool formatRequired) override;

        CalculationNumberResults calculation(std::string Formula) override;
    };

}

#endif //MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATION_H
