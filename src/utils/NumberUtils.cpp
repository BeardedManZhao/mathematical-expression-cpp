//
// Created by Liming on 2023/6/19.
//
#include <cmath>
#include "Utils.h"
#include "ConstantRegion.h"
#include "MExceptional.h"

namespace NumberUtils {
    /**
     * 将一个数值的十倍计算出来
     *
     * @param number 需要被计算的数值
     * @return 数值的十倍数值
     */
    int tenfold(int number) {
        return (number << 3) + (number << 1);
    }

    /**
     * 将一个数值乘以10的n次方
     *
     * @param number 需要被做乘法的数值
     * @param n      次方数量
     * @return number * 10的n次方
     */
    int PowerOfTen(int number, int n) {
        int res = number;
        for (int i = 1; i < n; i++) {
            res = tenfold(res);
        }
        return res;
    }

    /**
     * 计算一个数值的绝对值
     * @param x 需要被计算的数值
     * @return 被计算数值的绝对值
     */
    int absoluteValue(int x) {
        return abs(x);
    }

    /**
     * 计算一个数值的绝对值
     * @param x 需要被计算的数值
     * @return 被计算数值的绝对值
     */
    double absoluteValue(double x) {
        return x < 0 ? -x : x;
    }

    /**
     * 返回两个数值中的最大数值
     * @param v1 需要用于比较的数值
     * @param v2 需要用于比较的数值
     * @return 两个数值中较大的数值
     */
    double max(double v1, double v2) {
        return v1 > v2 ? v1 : v2;
    }

    /**
     * 将两个操作符级别进行比较
     *
     * @param s1 操作符1
     * @param s2 操作符2
     * @return s1操作符的优先级 是否小于 s2操作符的优先级
     */
    bool PriorityComparison(char s1, char s2) {
        return (s1 == PLUS_SIGN || s1 == MINUS_SIGN) &&
               (s2 == MULTIPLICATION_SIGN || s2 == DIVISION_SIGN || s2 == REMAINDER_SIGN);
    }

    /**
     * 计算一个数值的结果
     *
     * @param CalculationType 计算类型
     * @param an              运算数值1
     * @param bn              运算数值2
     * @return 运算结果
     */

    double calculation(char CalculationType, double an, double bn) {
        switch (CalculationType) {
            case PLUS_SIGN:
                return an + bn;
            case MINUS_SIGN:
                return an - bn;
            case MULTIPLICATION_SIGN:
                return an * bn;
            case DIVISION_SIGN:
                return an / bn;
            case REMAINDER_SIGN:
                return fmod(an, bn);
            default:
                std::string data = &"操作数计算异常，您的计算模式不存在，错误的计算模式 = ["[CalculationType];
                throw ME::AbnormalOperation(data.append(+"]\n").append(
                                &"Operand calculation exception. Your calculation mode does not exist. Wrong calculation mode = ["[CalculationType])
                                                    .append("]"));
        }
    }

    bool ComparisonOperation(const std::string &ComparisonOperator, double left, double right) {
        {
            if (std::equal(LESS_THAN_SIGN.begin(), LESS_THAN_SIGN.end(), ComparisonOperator.begin()))
                return left < right;
            else if (std::equal(GREATER_THAN_SIGN.begin(), GREATER_THAN_SIGN.end(), ComparisonOperator.begin()))
                return left > right;
            else if (std::equal(LESS_THAN_OR_EQUAL_TO_SIGN.begin(), LESS_THAN_OR_EQUAL_TO_SIGN.end(),
                                ComparisonOperator.begin()))
                return left <= right;
            else if (std::equal(GREATER_THAN_OR_EQUAL_TO_SIGN.begin(), GREATER_THAN_OR_EQUAL_TO_SIGN.end(),
                                ComparisonOperator.begin()))
                return left >= right;
            else if (std::equal(EQUAL_SIGN1.begin(), EQUAL_SIGN1.end(), ComparisonOperator.begin()) ||
                     std::equal(EQUAL_SIGN2.begin(), EQUAL_SIGN2.end(), ComparisonOperator.begin()))
                return left == right;
            else if (std::equal(NOT_EQUAL_SIGN1.begin(), NOT_EQUAL_SIGN1.end(), ComparisonOperator.begin()) ||
                     std::equal(NOT_EQUAL_SIGN2.begin(), NOT_EQUAL_SIGN2.end(), ComparisonOperator.begin()))
                return left != right;
            else {
                std::string data = "无法进行比较运算，因为有错误的运算符。\n";
                data.append("The comparison operation cannot be performed because there is an incorrect operator.\n")
                        .append("Bad comparison operator => ")
                        .append(ComparisonOperator);
                throw ME::AbnormalOperation(data);
            }
        }
    }

    /**
     * 带有步长的方式计算一个区间内所有数值的累加
     *
     * @param start 区间起始数值
     * @param end   区间终止数值
     * @return 区间内元素之和
     */
    double sumOfRange(double start, double end) {
        if (start == end) {
            return start;
        }
        return (start + end) * (absoluteValue(end - start) + 1) / 2;
    }

    /**
     * 带有步长的方式计算一个区间内所有数值的累加
     *
     * @param start 区间起始数值
     * @param end   区间终止数值
     * @param step  区间内每一个元素之间的步长
     * @return 区间内元素之和
     */
    double sumOfRange(double start, double end, double step) {
        if (step == 1) return sumOfRange(start, end);
        if (start == end) {
            return start;
        }
        double abs = absoluteValue(end - start);
        end -= fmod(abs, step);
        abs = absoluteValue(end - start);
        double n = 1 + (abs / step);
        return n * start + n * (n - 1) * (max(step, 2.0)) / 2;
    }


}