//
// Created by Liming on 2023/6/20.
//

#include "BracketsCalculation.h"
#include "ConstantRegion.h"
#include "Utils.h"
#include "MExceptional.h"

namespace ME {
    string BracketsCalculation::formatStr(std::string string) {
        return std::regex_replace(string, ME::ALL_INVISIBLE_CHARACTERS_PATTERN, NO_CHAR);
    }

    string BracketsCalculation::getName() {
        return "BracketsCalculation";
    }

    void BracketsCalculation::check(std::string string) {
        if (string.empty()) {
            throw ME::WrongFormat("您传入的表达式为null或为空 无法进行计算。");
        }
        unsigned int lastIndex = string.length() - 1;
        // 左括号出现数量
        int LeftCount = 0;
        // 右括号出现数量
        int RightCount = 0;
        {
            char lastChar = string[lastIndex];
            while (lastChar == EMPTY) {
                lastChar = string[--lastIndex];
            }
            if (!StrUtils::IsANumber(lastChar)) {
                if (lastChar != RIGHT_BRACKET) {
                    throw ME::WrongFormat(
                            &"您传入的表达式格式有误，最后一个字符不是一个数值！！！\nThe format of the expression you passed in is incorrect. The last character is not a numeric value!!!\nERROR => "[lastChar]
                    );
                }
            }
        }
        // 上一个字符是否是运算符
        bool is = false;
        int index = 0;
        for (const auto &c: string) {
            if (c == LEFT_BRACKET) {
                ++LeftCount;
            } else if (c == RIGHT_BRACKET) {
                ++RightCount;
            } else if (!(StrUtils::IsANumber(c) || c == DECIMAL_POINT || c == EMPTY)) {
                if (!StrUtils::IsAnOperator(c)) {
                    std::string data = "解析表达式的时候出现了未知符号!!!\nUnknown symbol appears when parsing expression!!!\nWrong format => [";
                    data += c;
                    throw ME::WrongFormat(data.append("] from " + string));
                } else {
                    if (is && c != MINUS_SIGN && c != PLUS_SIGN)
                        throw ME::WrongFormat(
                                "您的数学表达式不正确，缺失了一个运算数值或多出了一个运算符。ERROR => " + string);
                    is = true;
                    continue;
                }
            }
            if (++index > lastIndex) {
                break;
            }
            is = false;
        }
        if (LeftCount != RightCount) {
            int absV = abs(LeftCount - RightCount);
            std::string data =
                    "您的格式不正确，出现了数学表达式中不正确的括号对数，请您检查是否缺少或者多出了[" +
                    to_string(absV);
            data
                    .append(data + "]个括号。\n")
                    .append("Your format is incorrect. There are incorrect parenthesis logarithms in the mathematical expression. Please check whether [")
                    .append(to_string(absV))
                    .append("] parentheses are missing or extra.\n")
                    .append("Wrong from [" + string + "]");
            throw ME::WrongFormat(data);
        }
    }
}
