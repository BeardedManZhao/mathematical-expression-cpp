//
// Created by Liming on 2023/6/27.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_FASTSUMOFINTERVALSBRACKETS_H
#define MATHEMATICAL_EXPRESSION_CPP_FASTSUMOFINTERVALSBRACKETS_H

#include "BracketsCalculationTwo.h"
#include "SharedCalculation.h"

namespace ME {

    /**
     * 快速的将一个等差区间中的所有数值之和计算出来，在该计算组件中的公式由两个组成，例如 "a+b,a+b+10"，会将a+b+1 + a+b+2 + a+b+3 +...+a+b+10 的结果计算出来。
     * <p>
     * Quickly calculate the sum of all values in an isochromatic interval. The formula in this calculation component consists of two components, such as "a+b, a+b+10". The result of a+b+1+a+b+2+a+b+3+...+a+b+10 will be calculated.
     *
     * @author zhao
     */
    class FastSumOfIntervalsBrackets : public NumberCalculation, public SharedCalculation {

    private:
        bool StartSharedPool = true;
        string CurrentOwner;
        string left;
        string right;
        CalculationNumberResults shareNumberCalculation = CalculationNumberResults(
                -1, -1, "null"
        );

    public:

        int step = 1;

        string formatStr(std::string string) override;

        void check(std::string string) override;

        ME::CalculationNumberResults operator>>(std::string &format);

        ME::CalculationNumberResults operator<<(std::string &format);

        string getName() override;

        /**
         * 将两个结果对象，作为需要求和区间的起始与终止数值，以此进行区间的求和，不进行公式的计算
         * <p>
         * Take the two result objects as the starting and ending values of the interval to be summed, so as to sum the interval, without calculating the formula
         *
         * @param start 起始点结果数值
         * @param end   终止点结果数值
         * @return 区间求和的结果对象
         * <p>
         * Result object of interval summation
         */
        CalculationNumberResults calculation(CalculationNumberResults start, const CalculationNumberResults &end);

        /**
         * 将两个公式作为求和区间的起始与种植点，以此进行区间的求和，不进行共享池的相关判断
         * <p>
         * The two formulas are used as the starting point and planting point of the summation interval, so as to sum the interval without making relevant judgments on the shared pool
         *
         * @param f1 起始点计算公式
         * @param f2 终止点计算公式
         * @return 区间求和的结果对象
         * <p>
         * Result object of interval summation
         */
        CalculationNumberResults calculation(string f1, string f2);

        CalculationNumberResults calculation(std::string Formula, bool formatRequired) override;

        bool isStartSharedPool() override;

        void setStartSharedPool(bool startSharedPool) override;

    private:
        CalculationNumberResults calculation(std::string Formula) override;
    };

} // ME

#endif //MATHEMATICAL_EXPRESSION_CPP_FASTSUMOFINTERVALSBRACKETS_H
