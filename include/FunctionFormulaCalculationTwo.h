//
// Created by zhao on 2023/6/22.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATIONTWO_H
#define MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATIONTWO_H

#include "FunctionFormulaCalculation.h"

namespace ME {

    class FunctionFormulaCalculationTwo : public FunctionFormulaCalculation {
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

#endif //MATHEMATICAL_EXPRESSION_CPP_FUNCTIONFORMULACALCULATIONTWO_H
