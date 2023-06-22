//
// Created by Liming on 2023/6/21.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATION_H

#include "Calculation.h"
#include "CalculationResults.h"

namespace ME {
    class BooleanCalculation : public Calculation {
    public:
        std::string formatStr(std::string string) override;

        void check(std::string string) override;

        virtual CalculationBooleanResults operator>>(std::string &format) = 0;

        virtual CalculationBooleanResults operator<<(std::string &format) = 0;

        std::string getName() override;

        virtual CalculationBooleanResults calculation(std::string Formula, bool formatRequired) = 0;

    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_BOOLEANCALCULATION_H
