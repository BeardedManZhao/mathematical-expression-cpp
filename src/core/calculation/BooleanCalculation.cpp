//
// Created by Liming on 2023/6/21.
//

#include "BooleanCalculation.h"
#include "ConstantRegion.h"
#include "BracketsCalculationTwo.h"
#include "MExceptional.h"

static ME::BracketsCalculationTwo BRACKETS_CALCULATION_2;

std::string ME::BooleanCalculation::formatStr(std::string string) {
    return std::regex_replace(string, ALL_INVISIBLE_CHARACTERS_PATTERN, NO_CHAR);
}

void ME::BooleanCalculation::check(std::string string) {
    // 先按照表达式的比较运算符进行一个切分
    std::regex_iterator<std::string::iterator> rit(string.begin(), string.end(),
                                                   ME::REGULAR_COMPARISON_OPERATOR_PATTERN);
    std::regex_iterator<std::string::iterator> rend;
    // 判断是否属于布尔表达式，使用切分之后是否有两个表达式判断
    unsigned int length = rit->size();
    if (length == 2) {
        // 检查表达式两边是否符合条件
        std::string left = rit->str(), right = rit++->str();
        if (!std::equal(STRING_NULL.begin(), STRING_NULL.end(), left.begin())) {
            BRACKETS_CALCULATION_2.check(left);
        }
        if (!std::equal(STRING_NULL.begin(), STRING_NULL.end(), right.begin())) BRACKETS_CALCULATION_2.check(right);
    } else {
        // 如果比较运算符两边的表达式不是2个，说明不是一个布尔表达式
        std::string data = "发生了错误，您的布尔表达式中，存在着数量不正确的比较运算符\n";
        data.append("An error has occurred. There is an incorrect number of comparison operators in your Boolean expression\n")
                .append("Number of comparison operators [").append(to_string((length - 1))).append("]");
        throw ME::WrongFormat(data);
    }

}

std::string ME::BooleanCalculation::getName() {
    return "BooleanCalculation";
}




