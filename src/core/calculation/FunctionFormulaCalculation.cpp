//
// Created by zhao on 2023/6/22.
//

#include "FunctionFormulaCalculation.h"
#include "MEStack.h"
#include "Utils.h"
#include "ConstantRegion.h"
#include "CalculationConstant.h"
#include "MExceptional.h"
#include "BracketsCalculationTwo.h"
#include "FunctionManager.h"

static ME::BracketsCalculationTwo BRACKETS_CALCULATION_2 = ME::CalculationConstant::getBracketsCalculationTwo();

string ME::FunctionFormulaCalculation::formatStr(std::string string) {
    return regex_replace(string, ALL_INVISIBLE_CHARACTERS_PATTERN, NO_CHAR);
}

void ME::FunctionFormulaCalculation::check(std::string string) {
    // 将所有函数进行提取
    ME::MEStack<int> start;
    ME::MEStack<int> end;
    std::string stringBuilder;
    // 创建一个标记，标记是否进入函数
    bool b = false;
    int count = 0;
    int index = -1;
    for (const auto &aChar: string) {
        ++index;
        if (((aChar >= BA_ASCII && aChar <= BZ_ASCII) || (aChar >= SA_ASCII && aChar <= SZ_ASCII))) {
            if (!b) {
                // 如果是刚刚进入函数，就将当前索引添加到栈
                b = true;
                start.push(index);
            }
            // 如果当前是函数的名字，就将函数起始索引继续移动，将函数名字部分的索引去除
            start.push(start.pop_get() + 1);
        } else if (b && aChar == LEFT_BRACKET) {
            count += 1;
        } else if (b && aChar == RIGHT_BRACKET && --count == 0) {
            // 如果是函数结束，就将函数的终止点索引添加到栈
            b = false;
            end.push(index);
        } else if (!b && aChar != EMPTY) {
            stringBuilder += aChar;
        }
    }
    // 迭代所有的函数公式，判断是否有错误
    int size = start.size();
    int size1 = end.size();
    if (size == size1) {
        for (int i = 0; i < size; i++) {
            unsigned int start_index = start.pop_get() + 2;
            BRACKETS_CALCULATION_2.check(string.substr(start_index, end.pop_get() - start_index));
            stringBuilder += '0';
        }
        // 检查最终公式
        BRACKETS_CALCULATION_2.check(stringBuilder);
    } else {
        throw ME::WrongFormat(
                "函数可能缺少起始或结束括号，没有正常的闭环。\nThe function may lack a start or end bracket, and there is no normal closed loop\nMissing function bracket logarithm: " +
                to_string(NumberUtils::absoluteValue(size - size1))
        );
    }
}

string ME::FunctionFormulaCalculation::getName() {
    return "FunctionFormulaCalculation";
}

ME::CalculationNumberResults ME::FunctionFormulaCalculation::calculation(std::string Formula, bool formatRequired) {
    // 创建一个公式缓冲区
    string stringBuilder;
    {
        // 创建变量，负责记录函数的起始索引
        int start = 0;
        // 创建一个计数器，统计括号对数
        int count = 0;
        // 创建一个状态，统计是否进入函数
        bool setOk = false;
        // 创建一个字符缓冲区，用于存储函数的名字
        string name;
        // 开始迭代公式，找到函数的索引值
        int index = -1;
        for (const auto &aChar: Formula) {
            ++index;
            if (((aChar >= BA_ASCII && aChar <= BZ_ASCII) || (aChar >= SA_ASCII && aChar <= SZ_ASCII))) {
                // 如果是字母，代表当前就是函数的起始点，将这个函数的名字存储到临时缓冲区
                if (!setOk) {
                    start = index;
                    setOk = true;
                }
                name += aChar;
            } else if (setOk && aChar == LEFT_BRACKET) {
                // 如果是一个左括号 同时当前属于函数范围内，就为计数器加1
                count += 1;
            } else if (setOk && aChar == RIGHT_BRACKET && --count == 0) {
                // 如果当前区域是函数内，同时当前是一个右括号，而且该括号是与起始括号相对应的，代表函数结束
                setOk = false;
                // 通过函数名字获取到函数组件
                auto functionByName = FunctionManager::getFunction(name);
                // 使用括号计算组件，计算出函数实参，然后通过函数将函数内的公式计算出来
                unsigned int start_index = start + name.length() + 1;
                double args = BRACKETS_CALCULATION_2.calculation(Formula.substr(start_index, index - start_index + 2),
                                                                 formatRequired).getResult();
                double run = functionByName(&args);
                name.clear();
                // 将当前的函数结果添加到公式缓冲区，这里判断了下run的精度，如果run是一个整数，就直接转换成整数添加
                int run1 = (int) run;
                if (run == run1) {
                    stringBuilder.append(to_string(run1));
                } else {
                    stringBuilder.append(to_string(run));
                }
            } else if (!setOk && aChar != EMPTY) {
                // 如果是其他情况就直接将字符添加到公式中
                stringBuilder += aChar;
            }
        }
    }
    // 将当前不包含函数的公式使用括号表达式解析计算出来
    return BRACKETS_CALCULATION_2.calculation(stringBuilder, formatRequired);
}

ME::CalculationNumberResults ME::FunctionFormulaCalculation::calculation(std::string Formula) {
    return this->calculation(Formula, true);
}

ME::CalculationNumberResults ME::FunctionFormulaCalculation::operator>>(string &format) {
    return this->calculation(format);
}

ME::CalculationNumberResults ME::FunctionFormulaCalculation::operator<<(string &format) {
    return this->calculation(format);
}

