//
// Created by Liming on 2023/6/27.
//

#include "FastSumOfIntervalsBrackets.h"
#include "Utils.h"
#include "CalculationConstant.h"

static ME::BracketsCalculationTwo BRACKETS_CALCULATION_2 = ME::CalculationConstant::getBracketsCalculationTwo();

namespace ME {

    bool FastSumOfIntervalsBrackets::isStartSharedPool() {
        return this->StartSharedPool;
    }

    void FastSumOfIntervalsBrackets::setStartSharedPool(bool startSharedPool) {
        this->StartSharedPool = startSharedPool;
    }

    string FastSumOfIntervalsBrackets::formatStr(std::string string) {
        return StrUtils::trim(string);
    }

    void FastSumOfIntervalsBrackets::check(std::string string) {
        if (this->StartSharedPool && std::equal(this->CurrentOwner.begin(), this->CurrentOwner.end(), string.begin())) {
            // 如果共享池开启，同时共享池中的数据所属身份属于当前公式，并且有计算结果，就直接停止检查，因为这个公式之前检查过
            return;
        }
        // 在这里获取到前后两个公式
        vector<std::string> arrayList = StrUtils::splitByChar(string, COMMA);
        unsigned int size = arrayList.size();
        if (size == 2) {
            std::string l = arrayList[0];
            std::string r = arrayList[1];
            BRACKETS_CALCULATION_2.check(l);
            if (!std::equal(l.begin(), l.end(), r.begin())) {
                BRACKETS_CALCULATION_2.check(r);
            }
            if (this->StartSharedPool) {
                // 如果检查无误，就将检查之后的结果存储到共享池
                this->left = l;
                this->right = r;
                this->CurrentOwner = string;
            }
        } else {
            std::string data = "区间求和表达式解析错误，在该组件中的表达式，需要两个以逗号分割的表达式组成累加区间中的两个边界值。\n";
            data.append("Error parsing the interval summation expression. The expression in this component needs two expressions separated by commas to form two boundary values in the cumulative interval.")
                    .append("Number of expressions you provide => ");
            throw WrongFormat(data.append(to_string(size)));
        }
    }

    string FastSumOfIntervalsBrackets::getName() {
        return "FastSumOfIntervalsBrackets";
    }

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
    CalculationNumberResults
    FastSumOfIntervalsBrackets::calculation(CalculationNumberResults start, const CalculationNumberResults &end) {
        return {
                start.getResultLayers(),
                NumberUtils::sumOfRange(start.getResult(), end.getResult(), step),
                this->getName()
        };
    }

    CalculationNumberResults FastSumOfIntervalsBrackets::calculation(std::string Formula, bool formatRequired) {

        const bool equals =
                this->StartSharedPool && std::equal(Formula.begin(), Formula.end(), this->CurrentOwner.begin());
        if (equals) {
            // 如果共享池开启，同时共享池中数据所属没有错误，就使用共享池数据进行计算
            if (this->shareNumberCalculation.getResultLayers() != -1) {
                return this->shareNumberCalculation;
            }
            string start = left;
            string end = right;
            // 计算出结果数值
            CalculationNumberResults calculationNumberResults = calculation(start, end);
            this->shareNumberCalculation = calculationNumberResults;
            return calculationNumberResults;
        } else {
            // 如果是其他情况，代表共享池数据不可用，在这里获取出公式
            vector<string> arrayList = StrUtils::splitByChar(Formula, COMMA);
            string start = arrayList[0];
            string end = arrayList[1];
            // 计算出结果数值
            CalculationNumberResults calculationNumberResults = calculation(start, end);
            return calculationNumberResults;
        }
    }

    CalculationNumberResults FastSumOfIntervalsBrackets::calculation(string f1, string f2) {
        if (std::equal(f1.begin(), f1.end(), f2.begin())) {
            return BRACKETS_CALCULATION_2.calculation(f1, true);
        }
        return calculation(
                BRACKETS_CALCULATION_2.calculation(f1, true),
                BRACKETS_CALCULATION_2.calculation(f2, true)
        );
    }

    CalculationNumberResults FastSumOfIntervalsBrackets::calculation(std::string Formula) {
        return calculation(Formula, true);
    }

    ME::CalculationNumberResults FastSumOfIntervalsBrackets::operator>>(string &format) {
        return calculation(format);
    }

    ME::CalculationNumberResults FastSumOfIntervalsBrackets::operator<<(string &format) {
        return calculation(format);
    }


} // ME