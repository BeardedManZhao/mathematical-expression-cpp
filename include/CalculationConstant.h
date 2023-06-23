//
// Created by zhao on 2023/6/23.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_CALCULATIONCONSTANT_H
#define MATHEMATICAL_EXPRESSION_CPP_CALCULATIONCONSTANT_H

#include "BracketsCalculationTwo.h"

namespace ME {
    /**
     * 专用于被其它计算组件使用常量池，其中包含了被依赖的计算组件。
     *
     * Dedicated to being used by other computing components as a constant pool, which includes dependent computing components.
     */
    class CalculationConstant {
    public:

        /**
         *
         * @return 全局唯一的嵌套括号表达式计算组件，由于在库的内部，很多的计算组件依赖此库进行计算，因此使用一个全局的嵌套括号表达式来实现内存节约的效果。
         *
         * A globally unique nested parenthesis expression is used to calculate components. Due to the fact that many calculation components rely on this library for calculation, a globally unique nested parenthesis expression is used to achieve memory savings.
         */
        static BracketsCalculationTwo getBracketsCalculationTwo();
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_CALCULATIONCONSTANT_H
