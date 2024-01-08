//
// Created by Liming on 2023/6/18.
//

#include <regex>
#include "PrefixExpressionOperation.h"
#include "ConstantRegion.h"
#include "Utils.h"
#include "MExceptional.h"
#include "MEStack.h"

namespace ME {

    const std::regex REGULAR_ADDITION_SUBTRACTION_AMBIGUITY_REX(REGULAR_ADDITION_SUBTRACTION_AMBIGUITY);

    std::string PrefixExpressionOperation::formatStr(std::string string) {
        return std::regex_replace(string, REGULAR_ADDITION_SUBTRACTION_AMBIGUITY_REX, MINUS_SIGN_STR) + " + 0";
    }


    void PrefixExpressionOperation::check(std::string basicString) {
        unsigned long long last = basicString.size() - 1;
        char lastChar = basicString[last];
        while (lastChar == EMPTY) {
            lastChar = basicString[--last];
        }
        if (StrUtils::IsANumber(lastChar)) {
            bool is = false;
            for (int i = 0; i < last; i++) {
                char c = basicString[i];
                if (c == LEFT_BRACKET || c == RIGHT_BRACKET) {
                    std::string data = "组件" + this->getName() +
                                       "只能解析无括号的数学表达式，请将表达式中的括号去除。\nThe component " +
                                       this->getName() +
                                       " can only resolve mathematical expressions without parentheses. Please remove the parentheses from the expressions.";
                    throw WrongFormat(data);
                }
                if (!StrUtils::IsANumber(c) && c != DECIMAL_POINT && c != EMPTY) {
                    if (!StrUtils::IsAnOperator(c)) {
                        std::string data = "解析表达式的时候出现了未知符号!!!\nUnknown symbol appears when parsing expression!!!\nWrong format => [";
                        throw WrongFormat((data += c).append("] from " + basicString));
                    } else {
                        if (c != MINUS_SIGN && is)
                            throw WrongFormat("您的数学表达式不正确，缺失了一个运算数值或多出了一个运算符。ERROR => " +
                                              basicString);
                        is = true;
                        continue;
                    }
                }
                is = false;
            }
        } else {
            string data = "数学表达式的最后一个字符应是一个数值。\nThe last character of a mathematical expression should be a numeric value.\nERROR => ";
            throw WrongFormat(data + lastChar);
        }
    }

    CalculationNumberResults PrefixExpressionOperation::calculation(std::string Formula, bool formatRequired) {
        const std::string newFormula = formatRequired ? formatStr(Formula) : Formula;
        // 创建操作符栈
        ME::MEStack<double> doubleStack;
        // 创建操作数栈
        ME::MEStack<char> characterStack;
        // 开始格式化，将符号与操作数进行分类
        std::string stringBuilder;
        // 创建标记点 标记上一个是否是操作符
        bool backIsOpt = true;
        for (const auto &c: newFormula) {
            if (!backIsOpt && StrUtils::IsAnOperator(c)) {
                backIsOpt = true;
                // 如果是操作符，就先将上一个数值计算出来
                double number = StrUtils::stringToDouble(stringBuilder);
                if (characterStack.empty()) {
                    // 如果栈为空 直接将运算符添加到栈顶
                    characterStack.push(c);
                    // 将数值添加到数值栈顶
                    doubleStack.push(number);
                } else {
                    // 如果不为空就检查栈顶的与当前运算符的优先级
                    if (!NumberUtils::PriorityComparison(characterStack.top(), c)) {
                        // 如果上一个优先级较大 就将上一个操作符取出
                        char top = characterStack.top();
                        characterStack.pop();
                        // 将上一个优先级高的值 与当下优先级较低的值进行运算，然后将当下的新数值和当下的操作符推到栈顶
                        double v = doubleStack.top();
                        doubleStack.pop();
                        doubleStack.push(NumberUtils::calculation(top, v, number));
                        characterStack.push(c);
                    } else {
                        // 反之就将当前运算符提供到栈顶
                        characterStack.push(c);
                        doubleStack.push(number);
                    }
                }
                // 清理所有的字符缓冲
                stringBuilder.clear();
            } else if (c == DECIMAL_POINT || c == MINUS_SIGN || StrUtils::IsANumber(c)) {
                // 如果是数值的某一位，就将数值存储到变量中
                stringBuilder += c;
                backIsOpt = false;
            }
        }
        doubleStack.push(StrUtils::stringToDouble(stringBuilder));
        double res = doubleStack.get(0);
        char back;
        const unsigned long size = doubleStack.size();
        // 开始计算
        const unsigned long sizeD2 = size >> 1;
        int layer_num = 0;
        for (int i = 1, offset = 0; i < size && offset < sizeD2; ++offset, ++i) {
            // 更新操作符
            back = characterStack.get(offset);
            // 获取操作数并计算结果
            res = NumberUtils::calculation(back, res, doubleStack.get(i));
            ++layer_num;
        }
        // 返回结果
        return {layer_num, res, this->getName()};
    }

    ME::CalculationNumberResults PrefixExpressionOperation::operator>>(string &format) {
        return this->calculation(format);
    }

    string PrefixExpressionOperation::getName() {
        return "PrefixExpressionOperation";
    }

    CalculationNumberResults PrefixExpressionOperation::calculation(std::string Formula) {
        return this->calculation(Formula, true);
    }

    ME::CalculationNumberResults PrefixExpressionOperation::operator<<(string &format) {
        return operator>>(format);
    }
}