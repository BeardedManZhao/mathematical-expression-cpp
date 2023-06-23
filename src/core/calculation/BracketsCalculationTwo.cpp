//
// Created by Liming on 2023/6/20.
//

#include "BracketsCalculationTwo.h"
#include "ConstantRegion.h"

static ME::PrefixExpressionOperation operation;

ME::CalculationNumberResults ME::BracketsCalculationTwo::calculation(std::string Formula, bool formatRequired) {
    unsigned int length = Formula.length();
    // 公式存储区
    std::string stringBuilder;
    // 括号内数据的起始索引
    int start = 0;
    bool setOk = false;
    int layer = 0;
    // 括号内的括号均衡数量，为了确定是一对括号
    int count = 0;
    for (int i = 0; i < length; i++) {
        char aChar = Formula[i];
        if (aChar == LEFT_BRACKET) {
            // 如果当前字符是一个左括号，那么说明括号开始了，这个时候需要将起始点记录
            if (!setOk) {
                setOk = true;
                start = i + 1;
            }
            ++count;
        } else if (aChar == RIGHT_BRACKET && --count == 0) {
            setOk = false;
            // 如果当前字符是一个右括号，那么就将括号中的字符进行递归计算，计算之后将该参数作为公式的一部分
            CalculationNumberResults calculation = BracketsCalculationTwo::calculation(
                    Formula.substr(start, i - start + 1), formatRequired
            );
            stringBuilder.append(to_string(calculation.getResult()));
            ++layer;
        } else if (!setOk && aChar != EMPTY) {
            // 如果不是一个括号就将字符提供给字符串缓冲区
            stringBuilder += aChar;
        }
    }
    // 将此字符串的结果计算出来
    CalculationNumberResults calculationNumberResults = operation.calculation(stringBuilder,
                                                                              formatRequired);
    return {
            calculationNumberResults.getResultLayers() + layer,
            calculationNumberResults.getResult(),
            this->getName()
    };
}

string ME::BracketsCalculationTwo::formatStr(std::string string) {
    return BracketsCalculation::formatStr(string);
}

void ME::BracketsCalculationTwo::check(std::string string) {
    BracketsCalculation::check(string);
}

string ME::BracketsCalculationTwo::getName() {
    return BracketsCalculation::getName();
}

ME::CalculationNumberResults ME::BracketsCalculationTwo::operator>>(string &format) {
    return this->calculation(format, true);
}

ME::CalculationNumberResults ME::BracketsCalculationTwo::operator<<(string &format) {
    return this->calculation(format, true);
}
