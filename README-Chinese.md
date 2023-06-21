# ![image](https://user-images.githubusercontent.com/113756063/203919312-dcec4a61-2136-4af2-a361-66b2ed4e6a54.png) 数学表达式-cpp

- Switch to [English Document](https://github.com/BeardedManZhao/mathematical-expression-cpp/blob/main/README.md)

## 介绍

本框架是一种针对数学公式解析的有效工具，能够通过C++的API解析包含嵌套函数，包含函数，数列步长累加等数学公式，返回值是一个数值的结果对象，同时也可以进行比较运算的操作，再进行比较的时候，返回值是一个布尔值结果对象。
如果您是一位 Java 或 python爱好者，可以专门前往 [JavaAPI](https://github.com/BeardedManZhao/mathematical-expression.git)
或 [PythonAPI](https://github.com/BeardedManZhao/mathematical-expression-Py) 中进行相关资料的查阅。

### 如何使用库？

在项目中有一个 include 文件目录，其中存储的就是库需要的所有头文件，您可以将其中的库文件导入到您的项目中，然后再集成本框架编译好的dll，下面是cmake的配置文件实例。

```cmake
cmake_minimum_required(VERSION 3.23)
project(MyCpp)

set(CMAKE_CXX_STANDARD 14)

# 设置头文件目录（可以自定义）
include_directories(${PROJECT_SOURCE_DIR}/head)
add_executable(MyCpp main.cpp)
# 与项目进行链接（将库链接到编译之后的目标中）
target_link_libraries(${PROJECT_NAME} D:\\liming\\Project\\Clion\\MyCpp\\cmake-build-debug\\mathematical_expression_cpp.dll)
```

集成操作完毕之后，您可以尝试输入以下代码来判断库的功能是否正常，下面是该库的一个测试代码，如果其运行之后的程序main函数返回值为0
代表程序正常退出，意味着库装载完毕。

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 打印 mathematical_expression 的版本信息
    cout << mathematical_expression::getVERSION() << endl;
}
```

### 通过 mathematical-expression 库直接获取到计算组件并进行计算

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 构建需要计算的两种表达式
    string s1 = "1 + 20 - 2 + 4", s2 = "1 + 20 - (2 + 4)";
    // 获取到 me 门户类
    mathematical_expression me;
    // 获取到 无括号表达式计算组件
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // 获取到 有括号表达式计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
    // 开始检查表达式
    prefixExpressionOperation.check(s1);
    bracketsCalculationTwo.check(s2);
    // 开始计算两个表达式 可以使用左移运算符将表达式送给计算组件 获取到结果对象
    ME::CalculationNumberResults r1 = prefixExpressionOperation << s1;
    ME::CalculationNumberResults r2 = bracketsCalculationTwo << s2;
    // 开始进行结果查看
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r2 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- 运行结果

```
Active code page: 65001
计算层数：1     计算结果：23    计算来源：PrefixExpressionOperation
计算层数：1     计算结果：15    计算来源：PrefixExpressionOperation

进程已结束,退出代码0
```

## 框架架构

### 门户类

我们可以通过指定的门户类对象获取到相关的各个计算组件，这里与 JavaAPI 和 PythonAPI 的实现有些不同，这里是使用的get函数获取到指定计算组件对象，而非使用
Hash 缓冲池。

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 获取到 me 门户类
    mathematical_expression me;
    // 获取到 无括号表达式计算组件
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // 获取到 有括号表达式计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
}
```

## 计算组件

### 无括号表达式

- 类组件：core.calculation.number.PrefixExpressionOperation
- 介绍

  针对一个没有括号，但是有加减乘除以及取余等运算操作的数学表达式而设计的组件，该组件可以实现带有优先级计算的功能，其中通过前缀表达式解析计算，将操作数与操作符一同存储到栈，在存储的同时配有计算优先级比较，如果当下的优先级较小，就先将上一个操作数与操作符与当前操作数进行运算，形成一个新的数值，然后再入栈。
- API使用示例

  该组件支持的运算符有： a+b a-b a*b a/b a%b

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 获取到 me 门户类
    mathematical_expression me;
    // 获取到 无括号表达式计算组件
    ME::PrefixExpressionOperation prefixExpressionOperation = me.getPrefixExpressionOperation();
    // 构建一个表达式
    string s = "1 + 2 + 4 * 10 - 3";
    // 开始检查表达式
    prefixExpressionOperation.check(s);
    // 开始计算两个表达式 可以使用左移运算符将表达式送给计算组件 获取到结果对象
    ME::CalculationNumberResults r1 = prefixExpressionOperation << s;
    // 开始进行结果查看
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- 运行结果

  在API调用中，对函数的运行结果进行了打印，可以看到，组件计算的返回值是一个结果集对象，在该对象中存储的就是很多有关计算结果相关的信息。

```
Active code page: 65001
计算层数：1     计算结果：40    计算来源：PrefixExpressionOperation

进程已结束,退出代码0
```

### 嵌套括号表达式

- 类组件：core.calculation.number.BracketsCalculation2
- 介绍：

  嵌套括号表达式解析组件，能够针对带有多个括号的数学表达式进行解析与结果计算，针对嵌套括号进行优先级的解析与计算，该组件依赖于“core.calculation.number.PrefixExpressionOperation”，在该组件中采用递归进行括号的解析，然后将最内层面的表达式提供给“core.calculation.number.PrefixExpressionOperation”进行计算。
- API使用示例

  该组件支持的运算符有： a+b a-b a*b a/b a%b ( )

```c++
#include "mathematical_expression.h"

int main(){
    system("chcp 65001");
    // 获取到 me 门户类
    mathematical_expression me;
    // 获取到 无括号表达式计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();
    // 构建一个表达式
    string s = "1 + 2 + 4 * (10 - 3)";
    // 开始检查表达式
    bracketsCalculationTwo.check(s);
    // 开始计算两个表达式 可以使用左移运算符将表达式送给计算组件 获取到结果对象
    ME::CalculationNumberResults r1 = bracketsCalculationTwo << s;
    // 开始进行结果查看
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName() << endl;
}
```

- 运行结果

  在API调用中，对表达式的计算结果进行了打印，可以看到，组件计算的返回值是一个数值结果对象，在该对象中存储的就是很多有关计算结果相关的信息。

```
Active code page: 65001
计算层数：2     计算结果：31    计算来源：BracketsCalculation

进程已结束,退出代码0
```

## C++API 特性

在 C++ 中，库具有更快的解析与计算速度，同时其具有更加庞大的功能，接下来针对C++中的特有功能来进行一个说明。

### 操作数之间的计算操作

通过计算组件计算出来的结果对象，其还具有运算功能，可以基于此方式来进行多个操作数之间的计算操作，接下来就是一个示例。

```
#include <mathematical_expression.h>

int main() {
    // 准备数学表达式对象
    mathematical_expression me;
    // 打印出数学表达式库的版本号
    std::cout << mathematical_expression::getVERSION() << endl;
    // 准备要被计算的数学表达式
    std::string f = "1 + (3 - 2) + 10";
    // 准备计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // 开始进行计算
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // 使用结果对象进行计算
    ME::CalculationNumberResults res2 = res1 + res1;
    std::cout << "res1 + res1 = " << res2 << "\t其结果的源 = " << res2.getCalculationSourceName() << endl;
}
```

- 运行结果

```
#include <mathematical_expression.h>

int main() {
    system("chcp 65001");
    // 准备数学表达式对象
    mathematical_expression me;
    // 打印出数学表达式库的版本号
    std::cout << mathematical_expression::getVERSION() << endl;
    // 准备要被计算的数学表达式
    std::string f = "1 + (3 - 2) + 10";
    // 准备计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // 开始进行计算
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // 使用结果对象进行计算
    ME::CalculationNumberResults res2 = res1 + res1;
    std::cout << "res1 + res1 = " << res2 << "\t其结果的源 = " << res2.getCalculationSourceName() << endl;
}
```

### 操作数中的别名操作

在经过计算组件计算之后，操作数中包含计算组件的类型名称，但是在C++中，由于有了操作数之间的计算特性，源名称就显得很混乱，因此可以使用下面的操作起别名称，这样就可以达到良好的效果。

接下来是一个有关别名操作的基本示例

```c++
#include <mathematical_expression.h>

int main() {
    // 准备数学表达式对象
    mathematical_expression me;
    // 打印出数学表达式库的版本号
    std::cout << mathematical_expression::getVERSION() << endl;
    // 准备要被计算的数学表达式
    std::string f = "1 + (3 - 2) + 10";
    // 准备计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // 开始进行计算
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // 打印出结果对象的源名称
    std::cout << res1.getCalculationSourceName() << endl;
    // 为 res1 设置别名
    res1.as("res1");
    // 再一次打印出结果对象的源名称
    std::cout << res1.getCalculationSourceName() << endl;
}
```

- 运行结果

```
1.0.0-mathematical_expression-C++
BracketsCalculation
res1

进程已结束,退出代码0

```

接下来是一个有关别名操作的有趣案例（操作数之间的计算 + 别名）

```c++
#include <mathematical_expression.h>

int main() {
    // 准备数学表达式对象
    mathematical_expression me;
    // 打印出数学表达式库的版本号
    std::cout << mathematical_expression::getVERSION() << endl;
    // 准备要被计算的数学表达式
    std::string f = "1 + (3 - 2) + 10";
    // 准备计算组件
    ME::BracketsCalculationTwo bracketsCalculationTwo = me.getBracketsCalculation2();

    // 开始进行计算
    ME::CalculationNumberResults res1 = bracketsCalculationTwo << f;
    // 为 res1 设置别名
    res1.as("res1");
    std::cout << res1 << endl;

    // 计算出 res2
    ME::CalculationNumberResults res2 = res1 + res1;
    // 为 res2 设置别名
    res2.as("res2");
    std::cout << res2 << endl;
    std::cout << res2.getCalculationSourceName() << endl;

    // 计算出 res3 在这里使用结果对象之间的运算操作，res3 = res2 - res1
    ME::CalculationNumberResults res3 = res2 - res1;
    std::cout << '[' << res3  << ']' << '\t' << res3.getCalculationSourceName() << endl;

    // 计算出 res4 在这里使用结果对象之间的运算操作，res4 = res3 * res1 = (res2 - res1) * res1
    ME::CalculationNumberResults res4 = res3 * res1;
    std::cout  << '[' << res4 << ']' << '\t' << res4.getCalculationSourceName() << endl;
}
```

- 运行结果

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
- Switch to [English Document](https://github.com/BeardedManZhao/mathematical-expression-cpp/blob/main/README.md)
- [mathematical-expression-Java](https://github.com/BeardedManZhao/mathematical-expression.git)
- [mathematical-expression-py](https://github.com/BeardedManZhao/mathematical-expression-Py)
