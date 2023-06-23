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
        static BracketsCalculationTwo getBracketsCalculationTwo();
    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_CALCULATIONCONSTANT_H
