//
// Created by zhao on 2023/6/22.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATIONTWO_H
#define MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATIONTWO_H

#include "BooleanCalculation.h"

namespace ME {
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
