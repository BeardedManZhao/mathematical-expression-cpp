//
// Created by zhao on 2023/6/22.
//

#include "FunctionFormulaCalculation.h"
#include "FunctionFormulaCalculationTwo.h"
#include "MEStack.h"
#include "Utils.h"
#include "ConstantRegion.h"
#include "CalculationConstant.h"
#include "MExceptional.h"
#include "BracketsCalculationTwo.h"
#include "FunctionManager.h"

static ME::BracketsCalculationTwo BRACKETS_CALCULATION_2 = ME::CalculationConstant::getBracketsCalculationTwo();

string ME::FunctionFormulaCalculationTwo::formatStr(std::string string) {
    return regex_replace(string, ALL_INVISIBLE_CHARACTERS_PATTERN, NO_CHAR);
}

/**
  * 提取出来一个公式中所有函数的名称，以及其函数形参的起始与终止索引值
  *
  * @param f         需要被解析的数学运算公式
  * @param start          公式中所有包含函数实参公式的起始索引值
  * @param end            公式中所有包含函数实参公式的的终止索引值
  * @param names          公式中所有包含函数的名字
  * @param formulaBuilder 公式缓冲区，这个用于存储转换之后的公式，当需要进行公式检查的时候才会使用到该参数
  */
void FunctionParameterExtraction(const std::string &f, ME::MEStack<int> &start, ME::MEStack<int> &end,
                                 ME::MEStack<string> &names, std::string &formulaBuilder) {
    // 创建一个标记，标记是否进入函数
    bool b = false;
    int count = 0;
    int index = 0;

    // 创建函数名称缓冲区
    std::string stringBuilder;
    for (const auto &aChar: f) {
        ++index;
        if (((aChar >= BA_ASCII && aChar <= BZ_ASCII) || (aChar >= SA_ASCII && aChar <= SZ_ASCII))) {
            if (!b) {
                // 如果是刚刚进入函数，就将当前索引添加到栈
                b = true;
                start.push(index);
                // 然后为缓冲的公式进行 0 的追加
                formulaBuilder += '0';
            }
            // 将当前函数名字字符添加到函数名称缓冲区
            stringBuilder += aChar;
            // 如果当前是函数的名字，就将函数起始索引继续移动，将函数名字部分的索引去除
            start.push(start.pop_get() + 1);
        } else if (b && aChar == LEFT_BRACKET) {
            count += 1;
        } else if (b && aChar == RIGHT_BRACKET && --count == 0) {
            // 如果是函数结束，就将函数的终止点索引添加到栈
            b = false;
            end.push(index);
            // 将函数的名称添加到栈
            names.push(stringBuilder);
            // 清理名称缓冲区
            stringBuilder.clear();
        } else if (!b && aChar != EMPTY) {
            // 其他情况就直接将字符添加到公式缓冲区中
            formulaBuilder += aChar;
        }
    }
}

/**
  * 提取出来一个公式中所有函数的名称，以及其函数形参的起始与终止索引值
  *
  * @param f         需要被解析的数学运算公式
  * @param start          公式中所有包含函数实参公式的起始索引值
  * @param end            公式中所有包含函数实参公式的的终止索引值
  * @param names          公式中所有包含函数的名字
  */
void FunctionParameterExtraction(const std::string &f, ME::MEStack<int> &start, ME::MEStack<int> &end,
                                 ME::MEStack<string> &names) {
    // 创建一个标记，标记是否进入函数
    bool b = false;
    int count = 0;
    int index = 0;

    // 创建函数名称缓冲区
    std::string stringBuilder;
    for (const auto &aChar: f) {
        ++index;
        if (((aChar >= BA_ASCII && aChar <= BZ_ASCII) || (aChar >= SA_ASCII && aChar <= SZ_ASCII))) {
            if (!b) {
                // 如果是刚刚进入函数，就将当前索引添加到栈
                b = true;
                start.push(index);
            }
            // 将当前函数名字字符添加到函数名称缓冲区
            stringBuilder += aChar;
            // 如果当前是函数的名字，就将函数起始索引继续移动，将函数名字部分的索引去除
            start.push(start.pop_get() + 1);
        } else if (b && aChar == LEFT_BRACKET) {
            count += 1;
        } else if (b && aChar == RIGHT_BRACKET && --count == 0) {
            // 如果是函数结束，就将函数的终止点索引添加到栈
            b = false;
            end.push(index);
            // 将函数的名称添加到栈
            names.push(stringBuilder);
            // 清理名称缓冲区
            stringBuilder.clear();
        }
    }
}

void ME::FunctionFormulaCalculationTwo::check(std::string string) {
    // 准备函数元数据缓冲区
    ME::MEStack<int> start;
    ME::MEStack<int> end;
    ME::MEStack<std::string> names;
    // 准备公式缓冲区
    std::string stringBuilder;
    // 开始进行公式函数元数据提取
    FunctionParameterExtraction(string, start, end, names, stringBuilder);
    if (stringBuilder.empty()) {
        return;
    }
    // 判断是否全部一致
    int size1 = start.size();
    int size2 = end.size();
    if (size1 == size2 && size1 == names.size()) {
        if (size1 == 0) {
            return;
        }
        // 如果一致，就进行函数内部每一个公式的检查 这里首先将函数中的每一个公式切割出来
        int startIndex = start.pop_get();
        for (const std::string &s: StrUtils::splitByChar(string.substr(startIndex, end.pop_get() - startIndex - 1),
                                                         COMMA)) {
            // 将每一个公式进行检查
            BRACKETS_CALCULATION_2.check(s);
        }
        // 如果函数没有问题就检查整个公式
        BRACKETS_CALCULATION_2.check(stringBuilder);
    } else {
        throw WrongFormat(
                &"函数可能缺少起始或结束括号，没有正常的闭环。\nThe function may lack a start or end bracket, and there is no normal closed loop\nMissing function bracket logarithm: "[NumberUtils::absoluteValue(
                        size2 - size1)]);
    }
}

string ME::FunctionFormulaCalculationTwo::getName() {
    return "FunctionFormulaCalculationTwo";
}

ME::CalculationNumberResults ME::FunctionFormulaCalculationTwo::calculation(std::string Formula, bool formatRequired) {
    ME::MEStack<int> start;
    ME::MEStack<int> end;
    ME::MEStack<std::string> names;
    // 开始进行公式函数元数据提取
    FunctionParameterExtraction(Formula, start, end, names);
    // 开始计算，首先迭代所有函数的公式与函数的名字，计算出来函数的结果
    while (!start.empty()) {
        int pop1 = start.pop_get();
        int pop2 = end.pop_get();
        string pop = names.pop_get();
        // 通过函数名字获取函数对象
        auto functionByName = FunctionManager::getFunction(pop);
        ME::MEStack<double> functionArguments;
        // 通过函数索引获取实参
        const string str = Formula.substr(pop1, pop2 - pop1);
        for (const string &s: StrUtils::splitByChar(str, COMMA)) {
            // 将每一个函数实参计算出来，存储到临时列表
            functionArguments.push(BRACKETS_CALCULATION_2.calculation(s, formatRequired).getResult());
        }
        // 将当前函数索引区间内的数据字符串替换为当前函数的运算结果
        long start_index = pop1 - pop.length() - 1;
        Formula.replace(start_index, pop2 - start_index, to_string(functionByName(functionArguments)));
    }
    return BRACKETS_CALCULATION_2 << Formula;
}

ME::CalculationNumberResults ME::FunctionFormulaCalculationTwo::calculation(std::string Formula) {
    return this->calculation(Formula, true);
}

ME::CalculationNumberResults ME::FunctionFormulaCalculationTwo::operator>>(string &format) {
    return this->calculation(format);
}

ME::CalculationNumberResults ME::FunctionFormulaCalculationTwo::operator<<(string &format) {
    return this->calculation(format);
}

