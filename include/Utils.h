//
// Created by zhao on 2023/6/18.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_UTILS_H
#define MATHEMATICAL_EXPRESSION_CPP_UTILS_H

#include <string>
#include "MExceptional.h"
#include "vector"

namespace StrUtils {

    /**
     * 判断一个字符是不是一个数值
     *
     * @param c 需要被判断的自读
     * @return 如果是一个数值，这里返回True
     */
    bool IsANumber(char num_str);

    /**
     * 判断一个字符是不是一个操作符
     *
     * @param c 需要被判断的字符
     * @return 如果是一个操作符就返回True
     */
    bool IsAnOperator(char c);

    /**
     * 将一个字符串转换为浮点数值
     *
     * @param s 需要被转换的字符串
     * @return 字符串转换的浮点数值
     */
    double stringToDouble(std::string s);

    /**
     * 将一个数值字符传换成一个数值
     *
     * @param c 需要被转换的字符
     * @return 转换之后的数值
     */
    int charToInteger(char c);

    /**
     * 按照字符来拆分一个字符串。
     * @param data 需要被拆分的字符串 。
     * @param splitChar 需要作为拆分符号的字符。
     * @return 拆分之后的所有子字符串组合成为的 vector 对象。
     */
    std::vector<std::string> splitByChar(const std::string &data, char splitChar);

    /**
     * 将一个字符串中的指定的子字符串替换成为新的字符串。
     * @param old_string 需要被替换的字符串
     * @param replace_string 被替换的子字符串
     * @param new_string 替换之后的新的子字符串
     * @return 替换之后的新字符串。
     */
    std::string
    replace(const std::string &old_string, const std::string &replace_string, const std::string &new_string);
}

namespace NumberUtils {
    /**
     * 将一个数值的十倍计算出来
     *
     * @param number 需要被计算的数值
     * @return 数值的十倍数值
     */
    int tenfold(int number);

    /**
     * 将一个数值乘以10的n次方
     *
     * @param number 需要被做乘法的数值
     * @param n      次方数量
     * @return number * 10的n次方
     */
    int PowerOfTen(int number, int n);

    /**
     * 计算一个数值的绝对值
     * @param x 需要被计算的数值
     * @return 被计算数值的绝对值
     */
    int absoluteValue(int x);

    /**
     * 将两个操作符级别进行比较
     *
     * @param s1 操作符1
     * @param s2 操作符2
     * @return s1操作符的优先级 是否小于 s2操作符的优先级
     */
    bool PriorityComparison(char s1, char s2);

    /**
     * 计算一个数值的结果
     *
     * @param CalculationType 计算类型
     * @param an              运算数值1
     * @param bn              运算数值2
     * @return 运算结果
     */
    double calculation(char CalculationType, double an, double bn);

    /**
     * 将两个数值进行比较
     *
     * @param ComparisonOperator 两个数值的比较运算符
     * @param left               左值
     * @param right              右值
     * @return 左值 与 右值 之间是否符合比较运算符的关系
     * <p>
     * Whether the left value and right value conform to the comparison operator
     */
    bool ComparisonOperation(const std::string &ComparisonOperator, double left, double right);
}

#endif //MATHEMATICAL_EXPRESSION_CPP_UTILS_H
