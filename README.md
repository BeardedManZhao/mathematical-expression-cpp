# ![image](https://user-images.githubusercontent.com/113756063/203919312-dcec4a61-2136-4af2-a361-66b2ed4e6a54.png) mathematical-expression-cpp

- 切换至 [中文文档](https://github.com/BeardedManZhao/mathematical-expression-cpp/blob/main/README-Chinese.md)

## introduce

This framework is an effective tool for Formula parsing. It can parse Formula including nested functions, including
functions, and sequence step accumulation through the C++API. The return value is a numerical result object. At the same
time, you can also perform comparison operations. When you compare again, the return value is a Boolean result object.
If you are a Java or Python enthusiast, you can specifically
visit [JavaAPI](https://github.com/BeardedManZhao/mathematical-expression.git)
Or [Python API](https://github.com/BeardedManZhao/mathematical-expression-Py) Search for relevant information in.

### How to use the library?

There is an include file directory in the project, where all the Header file required by the library are stored. You can
import the library files into your project, and then assemble the dll compiled by this framework. The following is an
example of the configuration file for cmake.

```cmake
cmake_minimum_required(VERSION 3.23)
project(MyCpp)

set(CMAKE_CXX_STANDARD 14)

# Set Header file directory (can be customized)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(MyCpp main.cpp)
# Link to the project (link the library to the compiled target)
target_link_libraries(${PROJECT_NAME} D:\\liming\\Project\\Clion\\MyCpp\\cmake-build-debug\\libmathematical_expression_cpp.dll)
```

After the integration operation is completed, you can try to enter the following code to determine whether the function
of the library is normal. The following is a test code of the library. If the return value of the main function of the
program after it runs is 0, it means the program exits normally, which means the library is loaded.

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 打印 mathematical_expression 的版本信息
    cout << mathematical_expression::getVERSION() << endl;
}
```

### Obtain calculation components directly through the mathematical expression library and perform calculations

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // Build two expressions that need to be evaluated
    string s1 = "1 + 20 - 2 + 4", s2 = "1 + 20 - (2 + 4)";
    // Obtain me portal class
    mathematical_expression me;
    // Obtaining an expression evaluation component without parentheses
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // Obtaining parenthesized expression evaluation component
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
    // 
    prefixExpressionOperation.check(s1);
    bracketsCalculationTwo.check(s2);
    // To start calculating two expressions, you can use the left shift operator to send the expression to the calculation component and obtain the result object
    ME::CalculationNumberResults r1 = prefixExpressionOperation << s1;
    ME::CalculationNumberResults r2 = bracketsCalculationTwo << s2;
    // Start viewing results
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r2 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- Running results

```
Active code page: 65001
计算层数：1     计算结果：23    计算来源：PrefixExpressionOperation
计算层数：1     计算结果：15    计算来源：PrefixExpressionOperation

进程已结束,退出代码0
```

## Framework architecture

### Portal class

We can obtain the relevant computing components through the specified portal class object, which is slightly different
from the implementation of Java API and Python API. Here, we use the get function to obtain the specified computing
component object, rather than using a hash buffer pool.

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // Obtain me portal class
    mathematical_expression me;
    // Obtaining an expression evaluation component without parentheses
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // Obtaining parenthesized expression evaluation component
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
}
```

## Computing Components

### Parenthesis free expression

- Class component：ME::PrefixExpressionOperation

- Introduction
  A component designed for a mathematical expression without parentheses, but with operations such as addition,
  subtraction, multiplication, division, and remainder. This component can implement a function with priority
  calculation. Through prefix expression parsing and calculation, the operand and operator are stored on the stack, and
  at the same time, there is a calculation priority comparison. If the current priority is smaller, Just perform an
  operation on the previous operand and operator with the current operand to form a new value, and then push it onto the
  stack.

- API usage examples
  The operators supported by this component are: a+b a-b a * b a/b a% b

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // Obtain me portal class
    mathematical_expression me;
    // Obtaining an expression evaluation component without parentheses
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // 构建一个表达式
    string s = "1 + 2 + 4 * 10 - 3";
    // Start checking expression
    prefixExpressionOperation.check(s);
    // To start calculating two expressions, you can use the left shift operator to send the expression to the calculation component and obtain the result object
    ME::CalculationNumberResults r1 = prefixExpressionOperation << s;
    // Start viewing results
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- Running results

  In the API call, the Running results of the function were printed, and it can be seen that the return value calculated
  by the component is a result set object, which stores a lot of information related to the calculation results.

```
Active code page: 65001
计算层数：1     计算结果：40    计算来源：PrefixExpressionOperation

进程已结束,退出代码0
```

### 嵌套括号表达式

- Class component：ME::BracketsCalculationTwo
- 介绍：

  嵌套括号表达式解析组件，能够针对带有多个括号的数学表达式进行解析与结果计算，针对嵌套括号进行优先级的解析与计算，该组件依赖于“core.calculation.number.PrefixExpressionOperation”，在该组件中采用递归进行括号的解析，然后将最内层面的表达式提供给“core.calculation.number.PrefixExpressionOperation”进行计算。
- API使用示例

  该组件支持的运算符有： a+b a-b a*b a/b a%b ( )

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // Obtain me portal class
    mathematical_expression me;
    // Obtaining an expression evaluation component without parentheses
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
    // Build an expression
    string s = "1 + 2 + 4 * (10 - 3)";
    // Start checking expression
    bracketsCalculationTwo.check(s);
    // To start calculating two expressions, you can use the left shift operator to send the expression to the calculation component and obtain the result object
    ME::CalculationNumberResults r1 = bracketsCalculationTwo << s;
    // Start viewing results
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- Running results

  In the API call, the Running results of the function were printed, and it can be seen that the return value calculated
  by the component is a result set object, which stores a lot of information related to the calculation results.

```
Active code page: 65001
计算层数：2     计算结果：31    计算来源：BracketsCalculation

进程已结束,退出代码0
```

### Interval accumulation expression

- Full class name：ME::CumulativeCalculation
- introduce

  In mathematical expressions, there is often such a formula. The content of the formula is shown in the following
  figure. You can see the number sequence operations that need to be accumulated.

  Then, you can use the Full class name above to achieve the purpose you need.

  ![img_1](https://user-images.githubusercontent.com/113756063/201575828-5b76af88-6040-430d-a54c-61faf5905594.png)

- API Usage Example

  The syntax level is almost the same as that of other components. The calculation example of the mathematical
  expression written in the component is shown below. What is shown here is the calculation of an accumulative
  mathematical formula.

```c++
#include "mathematical_expression.h"
int main() {
    system("chcp 65001");
    // Create a mathematical expression parsing library object
    mathematical_expression me;
    // Obtain a component for calculating cumulative mathematical expressions
    ME::CumulativeCalculation cumulativeCalculation = me.getCumulativeCalculation();
    // Construct a mathematical expression where 'n [1,10,1]' is similar to the accumulation symbol in mathematics. n will continue to increase within this interval, and each increase will be carried into the formula for calculation once
    // The last 1 in [1,10,1] represents an increase in step size, which can achieve the accumulation of different equivalences within the interval
    string s = "n[1,10,1] 2 * (n + 1)";
    // Check mathematical expressions
    cumulativeCalculation.check(s);
    // Calculation results
    ME::CalculationNumberResults results = cumulativeCalculation << s;
    // Print out the results
    cout << "计算层数：" << results.getResultLayers() << "\t计算结果：" << results << "\t计算来源：" << results.getCalculationSourceName() << endl;
}
```

- Running results

```
Active code page: 65001
计算层数：11    计算结果：130   计算来源：CumulativeCalculation

进程已结束,退出代码0
```

### Function operation expression

- Full class name：ME::FunctionFormulaCalculation
- introduce

  The framework also supports the operation of some functions. You can use the above classes to write mathematical
  expressions that require functions. It should be noted that all functions used in expressions need to be logically
  registered in "Calculation Management" so that functions can be accessed during calculation
- API Usage Example

```c++
#include <mathematical_expression.h>
#include "FunctionManager.h"
int main() {
    system("chcp 65001");
    // 准备函数 这里的函数的作用是将参数 * 2
    auto myFun = [](const double *v) {
        return *v * 2;
    };
    // 注册函数 将我们的函数注册成为 DoubleValue 的名称
    ME::FunctionManager::append("DoubleValue", myFun);
    // 构建一个数学表达式，表达式中使用到了函数 DoubleValue
    string s = "2 * DoubleValue(2 + 3) + 1";
    // 获取到 数学表达式解析库
    mathematical_expression me;
    // 获取到函数表达式计算组件
    auto functionFormulaCalculation = me.getFunctionFormulaCalculation();
    // 检查数学表达式
    functionFormulaCalculation.check(s);
    // 计算出结果
    ME::CalculationNumberResults results = functionFormulaCalculation << s;
    // 将结果打印出来
    cout << "计算层数：" << results.getResultLayers() << "\t计算结果：" << results << "\t计算来源：" << results.getCalculationSourceName() << endl;
}
```

- Running results

```
Active code page: 65001
计算层数：1     计算结果：21    计算来源：BracketsCalculation

进程已结束,退出代码0
```

## C++API characteristic

In C++, libraries have faster parsing and computation speeds, while also having larger functionalities. Next, we will
provide an explanation of the unique features in C++.

### Calculation operations between operands

The result object calculated by the calculation component also has calculation function, which can be used to perform
calculation operations between multiple operands based on this method. The following is an example.

```c++
#include <mathematical_expression.h>

int main() {
    // Prepare mathematical expression objects
    mathematical_expression me;
    // Print out the version number of the mathematical expression library
    std::cout << mathematical_expression::getVERSION() << endl;
    // Prepare mathematical expressions to be evaluated
    std::string f = "1 + (3 - 2) + 10";
    // Prepare calculation components
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // Start calculation
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // Using Result Objects for Calculations
    ME::CalculationNumberResults res2 = res1 + res1;
    std::cout << "res1 + res1 = " << res2 << "\t其结果的源 = " << res2.getCalculationSourceName() << endl;
}
```

- Running results

```
1.0.1-mathematical_expression-C++
res1 + res1 = 24        其结果的源 = (BracketsCalculation + BracketsCalculation)

进程已结束,退出代码0
```

### Alias operations in operands

After the calculation of the calculation component, the operand contains the type name of the calculation component.
However, in C++, due to the calculation characteristics between operands, the source name becomes very confusing.
Therefore, the following operation can be used to distinguish names, which can achieve good results.

Next is a basic example of alias operations

```c++
#include <mathematical_expression.h>

int main() {
    // Prepare mathematical expression objects
    mathematical_expression me;
    // Print out the version number of the mathematical expression library
    std::cout << mathematical_expression::getVERSION() << endl;
    // Prepare mathematical expressions to be evaluated
    std::string f = "1 + (3 - 2) + 10";
    // Prepare calculation components
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // Start calculation
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // Print the source name of the result object
    std::cout << res1.getCalculationSourceName() << endl;
    // Set alias for res1
    res1.as("res1");
    // Print the source name of the result object
    std::cout << res1.getCalculationSourceName() << endl;
}
```

- Running results

```
1.0.0-mathematical_expression-C++
BracketsCalculation
res1

进程已结束,退出代码0

```

Next is an interesting case study on alias operations (calculation between operands+aliases)

```c++
#include <mathematical_expression.h>

int main() {
    // Prepare mathematical expression objects
    mathematical_expression me;
    // Print out the version number of the mathematical expression library
    std::cout << mathematical_expression::getVERSION() << endl;
    // Prepare mathematical expressions to be evaluated
    std::string f = "1 + (3 - 2) + 10";
    // Prepare calculation components
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // Start calculation
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // Set alias for res1
    res1.as("res1");
    std::cout << res1 << endl;

    // Calculate res2
    ME::CalculationNumberResults res2 = res1 + res1;
    // Setting an alias for res2
    res2.as("res2");
    std::cout << res2 << endl;
    std::cout << res2.getCalculationSourceName() << endl;

    // Calculate res3 and use the operation between the result objects here, where res3=res2- res1
    ME::CalculationNumberResults res3 = res2 - res1;
    std::cout << '[' << res3  << ']' << '\t' << res3.getCalculationSourceName() << endl;

    // Calculate res4 using the operation between the result objects here, where res4=res3 * res1=(res2- res1) * res1
    ME::CalculationNumberResults res4 = res3 * res1;
    std::cout  << '[' << res4 << ']' << '\t' << res4.getCalculationSourceName() << endl;
}
```

- Running results

```
1.0.0-mathematical_expression-C++
12
24
res2
[12]    (res2 - res1)
[144]   ((res2 - res1) * res1)

进程已结束,退出代码0
```

<hr>

更多信息

- date: 2023-06-20
- 切换至 [中文文档](https://github.com/BeardedManZhao/mathematical-expression-cpp/blob/main/README-Chinese.md)
- [mathematical-expression-Java](https://github.com/BeardedManZhao/mathematical-expression.git)
- [mathematical-expression-py](https://github.com/BeardedManZhao/mathematical-expression-Py)

