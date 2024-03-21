//
// Created by zhao on 2024/3/21.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_EXPRESSIONFUNCTION_H
#define MATHEMATICAL_EXPRESSION_CPP_EXPRESSIONFUNCTION_H

#include <vector>
#include <ostream>
#include "Calculation.h"
#include "MEStack.h"
#include "FunctionFormulaCalculationTwo.h"

namespace ME {

    class ExpressionFunction : public std::function<double(ME::MEStack<double>)> {


    private:


        std::string funName;
        std::vector<std::string> expression;
        std::vector<unsigned int> indexList;
        std::size_t paramSize;
        std::string f;

    protected:
        /**
         * 构建一个函数对象
         *
         * @param functionFormulaCalculation 函数计算组件
         * @param name                       函数名字
         * @param expression                 函数的所有形参
         * @param paramSize                  函数的参数个数
         * @param indexList                  函数的参数索引 元素是形参索引，元素索引是在表达式中参数的顺序
         * @param f                          函数的字符串对象
         */
        ExpressionFunction(string funName, vector<string> expression, vector<unsigned int> indexList,
                           const vector<std::string> &paramSize, string f);

    public:

        /**
         * 解析表达式，得到函数对象
         *
         * @param expression 表达式字符串
         * @return 解析出来的函数对象
         * @throws WrongFormat 如果函数表达式的格式有错误，则抛出此异常
         */
        static ExpressionFunction parse(const std::string &expression);

        /**
          * 函数的运行逻辑实现
          *
          * @param numbers 这里是函数的数据输入对象，由框架向这里传递数据输入参数
          * @return 这里是数据经过函数转换之后的数据
          */
        double run(const ME::MEStack<double> &numbers) const;

        /**
         *
         * @return 当前函数能够支持的参数数量！
         * 在 C++ 版本的 API 中 函数对象目前不支持自动判断参数的正确情况，不过可以通过在外部调用此函数来手动的区分函数能够接收的参数！
         *
         * In the C++version of the API, function objects currently do not support automatically determining the correctness of parameters. However, it is possible to manually distinguish the parameters that a function can receive by calling this function externally!
         */
        size_t getParamsSize() const;

        /**
         * @return 函数的名称，每一个函数都必须要设置一个名称，便于在公式中使用函数
         * <p>
         * The name of a function. Each function must have a name set to facilitate the use of functions in formulas
         */
        std::string getName();

        double operator()(const ME::MEStack<double> &numbers) const;

        friend std::ostream &operator<<(std::ostream &os, ExpressionFunction &function);


    }; // ME
}

#endif //MATHEMATICAL_EXPRESSION_CPP_EXPRESSIONFUNCTION_H
