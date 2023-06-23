//
// Created by zhao on 2023/6/23.
//

#include "CumulativeCalculation.h"
#include "Utils.h"
#include "regex"

string ME::CumulativeCalculation::formatStr(std::string basicString) {
    // 先按照表达式的比较运算符进行一个切分
    std::sregex_token_iterator split(basicString.begin(), basicString.end(), ME::INTERVAL_EXTRACTION_PATTERN, -1);
    std::sregex_token_iterator rend;
    std::vector<std::string> res;
    // 获取到累加所属符号 // s0
    std::regex pattern(split++->str());
    // 获取到区间的起始，终止，等差值 // s1
    const vector<std::string> arrayList = StrUtils::splitByChar(split++->str(), COMMA);
    const double start = StrUtils::stringToDouble(arrayList[0]);
    const double end = StrUtils::stringToDouble(arrayList[1]);
    const double equalDifference = StrUtils::stringToDouble(arrayList[2]);
    // 获取公式位 // s2
    const string format = split->str();
    // 开始构造累加公式
    string stringBuilder;
    double v = start;
    while (v <= end) {
        // 将指定位置的累加符号，变更为当前数值
        stringBuilder.push_back(LEFT_BRACKET);
        stringBuilder.append(std::regex_replace(format, pattern, to_string(v)))
                .push_back(RIGHT_BRACKET);
        stringBuilder.push_back(PLUS_SIGN);
        v += equalDifference;
    }
    stringBuilder.erase(stringBuilder.length() - 1);
    return BracketsCalculationTwo::formatStr(stringBuilder);
}

void ME::CumulativeCalculation::check(std::string basicString) {
    // 判断是否存在区间
    std::sregex_token_iterator split(basicString.begin(), basicString.end(), ME::INTERVAL_EXTRACTION_PATTERN, -1);
    std::sregex_token_iterator rend;
    std::vector<std::string> res;
    while (split != rend) {
        res.push_back(split++->str());
    }
    if (res.size() == 3) {
        string s0 = res[0], s1 = res[1], s2 = res[2];
        // 如果满足上述条件代表有累加符号 有区间 有公式 所以现在判断区间内是否缺少东西
        if (StrUtils::splitByChar(s1, COMMA).size() == 3) {
            // 满足上述条件代表区间也没有问题，下面就是将需要计算的公式交给父类去检查
            BracketsCalculationTwo::check(StrUtils::replace(s2, s0, "0"));
        } else {
            const string data = "检查到公式的错误，区间的配置不正确哦！正确的区间配置：自变量名称[起始值，终止值，等差值]\nThe formula error is detected, and the interval configuration is incorrect! Correct interval configuration: argument name [start, end, equalDifference]";
            throw WrongFormat(data + "Wrong interval configuration => " + s1);
        }
    } else {
        const string data = "检查到公式的错误，公式的格式似乎不正确，正确示例：n[0,10,1](1+(n)*n)\nAn error is detected in the formula. The format of the formula seems incorrect. A correct example: n[0,10,1](1+(n)*n)\n";
        throw WrongFormat(data + "Wrong interval configuration => " + basicString);
    }
}

string ME::CumulativeCalculation::getName() {
    return "CumulativeCalculation";
}

ME::CalculationNumberResults ME::CumulativeCalculation::calculation(std::string Formula, bool formatRequired) {
    return BracketsCalculationTwo::calculation(formatRequired ? formatStr(Formula) : Formula, false);
}
