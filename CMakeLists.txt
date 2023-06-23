cmake_minimum_required(VERSION 3.23)
project(mathematical_expression_cpp)

set(CMAKE_CXX_STANDARD 11)

# 头文件存储目录设置
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(
        mathematical_expression_cpp SHARED
        src/core/container/CalculationResults.cpp include/CalculationResults.h
        include/Utils.h
        include/ConstantRegion.h
        src/core/manager/CalculationManagement.cpp include/CalculationManagement.h
        src/core/calculation/PrefixExpressionOperation.cpp
        src/exceptional/MExceptional.cpp include/MExceptional.h
        src/utils/NumberUtils.cpp src/utils/StrUtils.cpp src/dataContainer/MEStack.cpp include/MEStack.h include/PrefixExpressionOperation.h
        src/core/calculation/NumberCalculation.cpp include/NumberCalculation.h
        src/core/calculation/Calculation.cpp include/Calculation.h
        src/core/mathematical_expression.cpp include/mathematical_expression.h
        src/core/calculation/BracketsCalculation.cpp include/BracketsCalculation.h
        src/core/calculation/BracketsCalculationTwo.cpp include/BracketsCalculationTwo.h
        src/core/calculation/BooleanCalculation.cpp include/BooleanCalculation.h
        src/core/calculation/BooleanCalculationTwo.cpp include/BooleanCalculationTwo.h
        src/core/calculation/FunctionManager.cpp include/FunctionManager.h
        src/core/calculation/FunctionFormulaCalculation.cpp include/FunctionFormulaCalculation.h src/core/calculation/CalculationConstant.cpp include/CalculationConstant.h src/core/calculation/CumulativeCalculation.cpp include/CumulativeCalculation.h)

