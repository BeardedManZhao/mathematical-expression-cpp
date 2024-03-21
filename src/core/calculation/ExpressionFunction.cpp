//
// Created by zhao on 2024/3/21.
//
#include "ConstantRegion.h"
#include "CalculationConstant.h"
#include "ExpressionFunction.h"
#include <utility>
#include "MExceptional.h"
#include "Utils.h"
#include "FunctionFormulaCalculationTwo.h"

ME::FunctionFormulaCalculationTwo static FUNCTION_FormulaCalculationTwo = ME::CalculationConstant::getFunctionFormulaCalculationTwo();

/**
 * 参数提取器正则匹配
 */
const static std::regex pattern(REGULAR_PURE_LETTER + "(?!\\()");

namespace ME {

    std::ostream &operator<<(std::ostream &os, ExpressionFunction &function) {
        os << function.getName();
        return os;
    }

    ExpressionFunction::ExpressionFunction(std::string funName,
                                           std::vector<std::string> expression,
                                           std::vector<unsigned int> indexList,
                                           const std::vector<std::string> &paramSize,
                                           std::string f)
            : funName(std::move(funName)),
              expression(std::move(expression)), // 使用拷贝构造函数复制元素
              indexList(std::move(indexList)),   // 使用拷贝构造函数复制元素
              paramSize(paramSize.size()),
              f(std::move(f)) {
    }

    ExpressionFunction ExpressionFunction::parse(const std::string &expression) {
        // 获取函数的形参部分和函数表达式部分
        std::vector<std::string> parts = StrUtils::splitByChar(expression, '=');
        if (parts.size() != 2) {
            throw ME::WrongFormat("您的表达式不属于函数，期望的格式：【函数名】(参数1,参数2) = 数学表达式");
        }

        // 解析函数名
        std::string functionName;
        // 解析参数名列表
        std::vector<std::string> params;
        // 获取参数名
        std::string trim = parts[0];
        unsigned long lastIndex = trim.length() - 1;
        for (size_t i = 0; i < trim.length(); ++i) {
            char c = trim[i];
            if (c == LEFT_BRACKET) {
                functionName = trim.substr(0, i);
                continue;
            }
            if (c == RIGHT_BRACKET) {
                if (functionName.empty()) {
                    throw ME::WrongFormat("请您将函数名字写上!!!");
                }
                params = StrUtils::splitByChar(
                        trim.substr(functionName.length() + 1, lastIndex - functionName.length() - 2), ',');
                break;
            }
        }

        // 检查并准备表达式
        std::string formula = parts[1];

        std::vector<std::string> operationList;
        std::vector<unsigned int> paramIndexes;

        unsigned long backEnd = 0;

        std::smatch matcher;
        auto temp1_begin = formula.cbegin();
        auto temp1_end = formula.cend();
        while (std::regex_search(temp1_begin, temp1_end, matcher, pattern)) {
            const std::string group = matcher.str();
            const auto last_iter = params.end();
            const auto s_find = std::find(params.begin(), last_iter, group);
            if (s_find != last_iter) {
                unsigned int iParam = s_find - params.begin();
                // 代表找到了
                const auto f_begin = formula.cbegin();
                // 获取指向起始位置的指针 (matcher.position() + backEnd) 是起始位置在整个字符串中的索引
                std::string substring = StrUtils::trim(
                        StrUtils::create_string_from_iterators(temp1_begin, f_begin + (matcher.position() + backEnd)));
                unsigned long subLength = group.length();
                if (subLength == 0) {
                    subLength = 1;
                }

                const unsigned long subStringLength = substring.length();
                if (subStringLength != 0 || f_begin == temp1_begin) {
                    operationList.push_back(substring);
                    paramIndexes.push_back(iParam);
                }
                backEnd += subStringLength;
                backEnd += subLength;
                temp1_begin += subStringLength;
                temp1_begin += subLength;
            } else if (!StrUtils::IsANumberFromStr(group)) {
                string temp = "Unknown formal parameter [";
                temp += group;
                temp += "] comes from [";
                temp += formula + "].";
                throw ME::WrongFormat(temp);
            }
        }
        operationList.push_back(StrUtils::trim(formula.substr(backEnd)));

        if (functionName.empty()) {
            throw ME::WrongFormat("您的函数名提取失败，可能是格式错误，正确的格式示例:sum(a, b)，您的格式：" + trim);
        }

        return {
                functionName, operationList, paramIndexes, vector<string>(params), expression
        };
    }

    double ExpressionFunction::run(const ME::MEStack<double> &numbers) const {
        // 检查参数
        if (numbers.size() != this->getParamsSize()) {
            string temp = "参数不正确，期望参数数量为：" + to_string(this->getParamsSize()) +
                          "，实际参数数量为：" + std::to_string(numbers.size());
            temp += '[';
            for (int i = 0; i < numbers.size(); ++i) {
                temp += to_string(numbers.get(i));
                temp += ' ';
            }
            temp += ']';
            throw std::runtime_error(". 错误参数 => " + temp);
        }


        std::string str;
        {
            std::stringstream s;
            // 开始进行参数替换
            int index = 0;
            for (unsigned int integer: this->indexList) {
                s << this->expression[index++] << (to_string(numbers.get(integer)));
            }
            if (this->expression.size() > index) {
                s << this->expression[index];
            }
            // 完成
            str = s.str();
        }
        try {
            FUNCTION_FormulaCalculationTwo.check(str);
            CalculationNumberResults result = FUNCTION_FormulaCalculationTwo.calculation(str, false);
            return result.getResult();
        } catch (const WrongFormat &e) {
            string temp = "公式计算错误: ";
            temp += e.what();
            throw ME::WrongFormat(temp);
        }
    }

    std::string ExpressionFunction::getName() {
        return this->funName;
    }

    size_t ExpressionFunction::getParamsSize() const {
        return this->paramSize;
    }

    double ExpressionFunction::operator()(const MEStack<double> &numbers) const {
        return this->run(numbers);
    }

}