//
// Created by Liming on 2023/6/19.
//
#include "MExceptional.h"
#include "ConstantRegion.h"
#include "Utils.h"

namespace StrUtils {

    /**
     * 判断一个字符是不是一个数值
     *
     * @param c 需要被判断的自读
     * @return 如果是一个数值，这里返回True
     */
    bool IsANumber(char num_str) {
        return num_str >= 48 && num_str <= 57;
    }

    /**
     * 判断一个字符是不是一个操作符
     *
     * @param c 需要被判断的字符
     * @return 如果是一个操作符就返回True
     */
    bool IsAnOperator(char c) {
        switch (c) {
            case PLUS_SIGN:
            case MINUS_SIGN:
            case MULTIPLICATION_SIGN:
            case DIVISION_SIGN:
            case REMAINDER_SIGN:
            case POW_SIGN:
                return true;
            default:
                return false;
        }
    }

    /**
     * 将一个 ascii 数值转换成为字符串
     * @param ascii 需要被转换的 ascii 数值
     * @return 转换操作成功之后的字符串
     */
    std::string asciiToChar(int ascii) {
        return {char(ascii)};
    }

    /**
     * 将一个数值字符传换成一个数值
     *
     * @param c 需要被转换的字符
     * @return 转换之后的数值
     */
    int charToInteger(char c) {
        if (StrUtils::IsANumber(c)) {
            return c - 48;
        } else {
            std::string temp_ex_data = "您在进行字符与数值之间的转换时，由于字符的不正确导致无法成功转换";
            std::string temp_res = asciiToChar(c);
            temp_ex_data.append(
                            "\nWhen you are converting characters to numeric values, the conversion cannot be successful due to incorrect characters.")
                    .append(temp_res);
            throw ME::WrongFormat(temp_ex_data);
        }
    }

    /**
     * 将一个字符串转换为浮点数值
     *
     * @param s 需要被转换的字符串
     * @return 字符串转换的浮点数值
     */
    double stringToDouble(std::string s) {
        int floatRes = 0;
        int intRes = 0;
        int intSize = 0;
        int floatSize = 0;
        bool isInt = true;
        unsigned long long length = s.length();
        if (length <= 0) {
            throw ME::WrongFormat(
                    "您在调用 stringToDouble 函数的时候 不能传递空字符串！\nYou cannot pass an empty string when calling the stringToDouble function!");
        }
        // 判断是否为负数
        bool isF = s[0] == MINUS_SIGN;
        if (isF) {
            s = s.substr(1);
            length -= 1;
        }
        for (int i = 0; i < length; i++) {
            char c = s[i];
            if (c != DECIMAL_POINT && c != EMPTY) {
                // 如果当前不是小数点符号 就直接对数值进行位分配
                if (isInt) {
                    // 如果当前不是小数点符号 就直接将数值归为整数
                    intRes = NumberUtils::tenfold(intRes) + StrUtils::charToInteger(c);
                    intSize++;
                } else {
                    // 如果是小数点 就直接将数值归为小数
                    floatRes = NumberUtils::tenfold(floatRes) + charToInteger(c);
                    floatSize++;
                }
            } else if (c == DECIMAL_POINT) {
                // 如果是小数点 就判断是否发生精度问题，如果没有发生就切换添加状态
                if (!isInt) {
                    throw ME::AbnormalOperation("数值的浮点符号出现次数过多，无法计算" + s);
                } else if (intSize > 9) {
                    throw ME::AbnormalOperation("数值的整数部分数值位数过长，无法计算" + s);
                }
                isInt = false;
            }
        }
        if (floatSize > 9) {
            throw ME::AbnormalOperation("数值的小数部分数值位数过长，无法计算" + s);
        }
        // 计算出来数值本身
        const double res = intRes + floatRes / (double) NumberUtils::PowerOfTen(10, floatSize);
        // 判断是否为负数，如果不是负数直接返回值
        return isF ? -res : res;
    }

    std::vector<std::string> splitByChar(const std::string &data, char splitChar) {
        std::vector<std::string> res;
        std::string buffer;
        for (const auto &item: data) {
            if (item != splitChar) {
                buffer.push_back(item);
            } else {
                res.push_back(buffer);
                buffer = std::string();
            }
        }
        if (!buffer.empty()) {
            res.push_back(buffer);
        }
        return res;
    }

    /**
     * 将一个字符串中的指定的子字符串替换成为新的字符串。
     * @param old_string 需要被替换的字符串
     * @param replace_string 被替换的子字符串
     * @param new_string 替换之后的新的子字符串
     * @return 替换之后的新字符串。
     */
    std::string
    replace(const std::string &old_string, const std::string &replace_string, const std::string &new_string) {
        if (old_string.empty() || replace_string.empty()) {
            return "";
        }
        std::string res;
        unsigned int l = replace_string.size();
        for (unsigned int start = 0, end = l - 1; end < old_string.length(); ++start, ++end) {
            // 判断当前的子字符串是否需要被替换
            std::string subStr = old_string.substr(start, l);
            if (std::equal(subStr.begin(), subStr.end(), replace_string.begin())) {
                // 需要被替换
                res = res.replace(res.length() - l + 1, l, new_string);
            } else {
                // 不需要被替换
                if (start == 0) {
                    res.append(subStr);
                } else {
                    res += old_string[end];
                }
            }
        }
        return res;
    }

    /**
     * 使用起始与终止的指针进行拷贝字符串
     * @param start 起始的字符串指针
     * @param end 终止的字符串指针
     * @return 拷贝成功的字符串数据
     */
    std::string copy_str(std::string::const_iterator start, std::string::const_iterator end) {
        std::string buffer;
        while (start != end) {
            buffer.push_back(*(start++));
        }
        return buffer;
    }

    /**
     * 去除字符串前后空字符串的函数
     * @param data 需要被去除空值的字符串
     * @return 去除成功后返回的新字符串
     */
    std::string trim(const std::string &data) {
        // 获取到尾部指针
        std::string::const_iterator start = data.begin();
        std::string::const_iterator end = data.end();
        while (start != end && *start == ' ') {
            // 移动头部的指针，去除前面的空格
            ++start;
        }
        // 判断是否需要进行后向前的判断
        if (start == end) {
            // 不需要判断了，直接返回数值
            return "";
        }
        // 需要判断就继续迭代
        while (end != start && *end == ' ') {
            --end;
        }
        return copy_str(start, end);
    }

    // 函数接受一个字符串的引用和一对迭代器，返回从这对迭代器中构造的新字符串
    std::string create_string_from_iterators(std::string::const_iterator begin, std::string::const_iterator end) {
        return {
                begin, end
        }; // 使用迭代器范围构造新字符串
    }

    bool IsANumberFromStr(const std::string &num_str) {
        return std::all_of(num_str.begin(), num_str.end(), [](char c) { return std::isdigit(c); });
    }


}
