//
// Created by zhao on 2023/6/18.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CALCULATIONRESULTS_H
#define MATHEMATICAL_EXPRESSION_CPP_CALCULATIONRESULTS_H

#include <iostream>
#include "string"

using namespace std;

namespace ME {


    /**
     * 计算结果接口，其中一般用来存储有关计算结果的数据，结果数据不一定是一个数值，具体的操作请查阅子类实现
     * <p>
     * Calculation result interface, which is generally used to store data related to calculation results. The result data may not be a numerical value. Please refer to the subclass implementation for specific operations
     *
     * @author zhao
     */
    class CalculationResults {
        /**
         * 计算结果中是经历了很多层计算才获得到的，这个函数可以获取到计算结果的层数量，也可以说是计算结果的计算次数。
         * <p>
         * The calculation result is obtained after many layers of calculation. This function can obtain the number of layers of the calculation result, or the number of calculations of the calculation result.
         *
         * @return 计算结果的计算次数
         */
        virtual int getResultLayers() = 0;

        /**
         * 结果是被计算组件计算出来的，在这里可以查询到计算该结果的组件名称，需要注意的是，这里返回的名称不会随着管理者中注册表的更改而变化
         * <p>
         * The result is calculated by the calculation component. You can query the name of the component that calculates the result here. Note that the name returned here will not change with the change of the registry in the administrator
         *
         * @return 计算结果的来源，一般情况下，如果设置了别名，此函数将返回别名数据。
         *
         * The source of the calculation result. Generally, if an alias is set, this function will return the alias data.
         */
        virtual string getCalculationSourceName() = 0;

        /**
         * 从结果数据对象中提取出指定的数据
         * <p>
         * Extract the specified data from the result data object
         * @return 当前结果存储对象中存储的结果数值。
         *
         * The result value stored in the current result storage object.
         */
        virtual double getResult_double() const = 0;

        bool operator==(const CalculationResults &other) const {
            return this->getResult_double() == other.getResult_double();
        }

        size_t operator()(CalculationResults &r) const;
    };

    /**
     * 数值计算结果存储对象，在该类中存储的都是来自计算组件的计算结果，以及运算级别层数等信息
     * <p>
     * Numerical calculation result storage object. In this class, the calculation results from calculation components, as well as the number of operation levels and other information are stored
     *
     * @author zhao
     */
    class CalculationNumberResults : public CalculationResults {
    private:
        const double result;
        const int result_layers;
        const string source;
        string alias;

    public:
        /**
         * 构造出一个新的计算结果存储类
         * <p>
         * Construct a new calculation result storage class
         * <p>
         * @param result  已经计算出结果数值的情况下，使用该形参进行赋值
         *                <p>
         *                If the result value has been calculated, use this parameter for assignment
         * @param source  来源，表明该结果对象的计算来源。
         *                <p>
         *                Source indicates the calculation source of the result object.
         */
        CalculationNumberResults(int result_layers, double result, string source);

    public:
        int getResultLayers() override;

        string getCalculationSourceName() override;

        /**
         * 为结果对象起别名。
         *
         * Create an alias for the result object.
         * @param name 指定的新别名，此操作将会使得结果对象的源名称成为别名。
         *
         * Specify a new alias, which will make the source name of the result object an alias.
         */
        void as(const string &name);

        /**
         * clear alias
         */
        void clearAs();

        /**
         * 从结果数据对象中提取出指定的数据
         * <p>
         * Extract the specified data from the result data object
         * @return 当前结果存储对象中存储的结果数值。
         *
         * The result value stored in the current result storage object.
         */
        double getResult_double() const override;

        /**
         * 从结果数据对象中提取出指定的数据
         * <p>
         * Extract the specified data from the result data object
         * @return 当前结果存储对象中存储的结果数值。
         *
         * The result value stored in the current result storage object.
         */
        double getResult() const;

        /**
         * 清理类中的所有成员在内存中的占用
         * <p>
         * Clean up the memory usage of all members in the class
         */
        ~CalculationNumberResults();

        bool operator<(const CalculationNumberResults &rhs) const;

        bool operator>(const CalculationNumberResults &rhs) const;

        bool operator<=(const CalculationNumberResults &rhs) const;

        bool operator>=(const CalculationNumberResults &rhs) const;

        bool operator==(const CalculationNumberResults &rhs) const;

        bool operator!=(const CalculationNumberResults &rhs) const;

        size_t operator()(const CalculationNumberResults &person) const;
    };

    /**
     * 数值计算结果存储对象，在该类中存储的都是来自计算组件的计算结果，以及运算级别层数等信息
     * <p>
     * Numerical calculation result storage object. In this class, the calculation results from calculation components, as well as the number of operation levels and other information are stored
     *
     * @author zhao
     */
    class CalculationBooleanResults : public CalculationResults {
    private:
        const bool result;
        const string source;
        string alias;
        const int Layers;
        const double left;
        const double right;

    public:

        /**
         *
         * @param result
         * @param source
         * @param layers
         * @param left
         * @param right
         */
        CalculationBooleanResults(bool result, string source, int layers, double left,
                                  double right);

        ~CalculationBooleanResults();

        int getResultLayers() override;

        string getCalculationSourceName() override;

        /**
         * 为结果对象起别名。
         *
         * Create an alias for the result object.
         * @param name 指定的新别名，此操作将会使得结果对象的源名称成为别名。
         *
         * Specify a new alias, which will make the source name of the result object an alias.
         */
        void as(const string &name);

        /**
         * clear alias
         */
        void clearAs();

        /**
         * 从结果数据对象中提取出指定的数据
         * <p>
         * Extract the specified data from the result data object
         * @return 当前结果存储对象中存储的结果数值。
         * <p>
         * The result value stored in the current result storage object.
         */
        double getResult_double() const override;

        /**
         * 从结果数据对象中提取出指定的数据
         * <p>
         * Extract the specified data from the result data object
         * @return 当前结果存储对象中存储的结果数值。
         * <p>
         * The result value stored in the current result storage object.
         */
        bool getResult() const;

        /**
         * @return 从布尔结果数值中获取到 左值。
         */
        double getLeft() const;

        /**
         * @return 从布尔结果数值中获取到 左值。
         */
        double getRight() const;

        bool operator==(const CalculationBooleanResults &other) const;

        bool operator!=(const CalculationBooleanResults &other) const;

        size_t operator()(const CalculationBooleanResults &person) const;
    };

    CalculationNumberResults operator+(CalculationNumberResults v1, CalculationNumberResults v2);

    CalculationNumberResults operator-(CalculationNumberResults v1, CalculationNumberResults v2);

    CalculationNumberResults operator*(CalculationNumberResults v1, CalculationNumberResults v2);

    CalculationNumberResults operator/(CalculationNumberResults v1, CalculationNumberResults v2);

    CalculationNumberResults operator<<(CalculationNumberResults v1, CalculationNumberResults v2);

    CalculationNumberResults operator>>(CalculationNumberResults v1, CalculationNumberResults v2);
}

ostream &operator<<(ostream &out, const ME::CalculationBooleanResults *rhs);

ostream &operator<<(ostream &out, const ME::CalculationBooleanResults &rhs);

ostream &operator<<(ostream &out, const ME::CalculationNumberResults *rhs);

ostream &operator<<(ostream &out, const ME::CalculationNumberResults &rhs);

#endif //MATHEMATICAL_EXPRESSION_CPP_CALCULATIONRESULTS_H
