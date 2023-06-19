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
}