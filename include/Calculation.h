//
// Created by Liming on 2023/6/19.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CALCULATION_H
#define MATHEMATICAL_EXPRESSION_CPP_CALCULATION_H

#include <string>

/**
 * 计算接口 其中提供不同计算组件针对数学公式的不同实现
 * <p>
 * The calculation interface provides different implementations of different calculation components for mathematical formulas
 *
 * @author zhao
 */
class Calculation {

public:
    explicit Calculation() = default;

    /**
     * 格式化一个公式 使得其可以被该计算组件进行运算
     * <p>
     * Format a formula so that it can be calculated by the calculation component
     *
     * @param string 数学运算公式
     * @return 格式化之后的数学运算公式
     */
    virtual std::string formatStr(std::string string) = 0;

    /**
     * 检查公式格式是否正确，如果不正确就会抛出一个异常
     * <p>
     * Check whether the formula format is correct. If not, an exception will be thrown
     *
     * @param string 需要被判断格式的数学运算公式
     *               <p>
     *               Mathematical operation formula of the format to be judged
     * @throws WrongFormat 在检查出来错误的时候进行该异常抛出，该异常中会记录格式检查时，查出来的格式错误。
     *                     <p>
     *                     The exception is thrown when an error is detected, and the format error found during the format check will be recorded in the exception.
     */
    virtual void check(std::string string) = 0;

    /**
     *
     * @return 当前计算组件的名称。
     */
    virtual std::string getName() = 0;

};

#endif //MATHEMATICAL_EXPRESSION_CPP_CALCULATION_H
