//
// Created by zhao on 2023/6/22.
//

#include "BooleanCalculationTwo.h"
#include "BracketsCalculationTwo.h"
#include "ConstantRegion.h"
#include "CalculationConstant.h"
#include "Utils.h"

static ME::BracketsCalculationTwo BRACKETS_CALCULATION_2 = ME::CalculationConstant::getBracketsCalculationTwo();

namespace ME {
    CalculationBooleanResults BooleanCalculationTwo::operator>>(std::string &format) {
        return this->calculation(format, true);
    }

    CalculationBooleanResults BooleanCalculationTwo::operator<<(std::string &format) {
        return this->calculation(format, true);
    }

    string BooleanCalculationTwo::formatStr(std::string string) {
        return BooleanCalculation::formatStr(string);
    }

    void BooleanCalculationTwo::check(std::string string) {
        BooleanCalculation::check(string);
    }

    string BooleanCalculationTwo::getName() {
        return BooleanCalculation::getName();
    }
}

ME::CalculationBooleanResults ME::BooleanCalculationTwo::calculation(std::string Formula, bool formatRequired) {
    string NewFormula = formatRequired ? BooleanCalculation::formatStr(Formula) : Formula;
    // 先按照表达式的比较运算符进行一个切分
    std::sregex_token_iterator rit(NewFormula.begin(), NewFormula.end(), ME::REGULAR_COMPARISON_OPERATOR_PATTERN, -1);
    std::sregex_token_iterator rend;
    std::vector<std::string> res;
    // 获取到左右两边的表达式
    string s1 = rit->str(), s2 = (++rit)->str();
    // 进行比较运算符的提取
    const unsigned int start = s1.length();
    unsigned int end = start + 1;
    while (!std::equal(s2.begin(), s2.end(), &NewFormula[end])) {
        ++end;
    }
    string s = NewFormula.substr(start, end - start + 2);
    {
        // 判断左右是否有一个为null
        if (std::equal(STRING_NULL.begin(), STRING_NULL.end(), s1.begin())) {
            // 如果左边为null ，同时右边为null就代表两个值相同，在这里直接将两个值赋值0
            double aNull = std::equal(STRING_NULL.begin(), STRING_NULL.end(), s2.begin()) ? 0 : 1;
            return {
                    NumberUtils::ComparisonOperation(s, 0, aNull),
                    this->getName(), 1, 0, aNull
            };
        } else if (std::equal(STRING_NULL.begin(), STRING_NULL.end(), s2.begin())) {
            // 如果左边不是null 但是 右边为null，就直接将 1 比较 0 的值算出来
            return {
                    NumberUtils::ComparisonOperation(s, 1, 0),
                    this->getName(), 1, 1, 0
            };
        }
    }
    // 进行左值的结果计算
    CalculationNumberResults calculation1 = BRACKETS_CALCULATION_2 << s1;
    // 进行右值的结果计算
    CalculationNumberResults calculation2 = BRACKETS_CALCULATION_2 << s2;
    // 进行表达式结果的计算
    double left = calculation1.getResult();
    double right = calculation2.getResult();
    return {NumberUtils::ComparisonOperation(s, left, right), this->getName(),
            calculation1.getResultLayers() + calculation2.getResultLayers(), left,
            right};
}