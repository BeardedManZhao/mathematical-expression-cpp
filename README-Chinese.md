# ![image](https://user-images.githubusercontent.com/113756063/203919312-dcec4a61-2136-4af2-a361-66b2ed4e6a54.png) 数学表达式-cpp

- Switch to [English Document](https://github.com/BeardedManZhao/mathematical-expression-cpp/blob/main/README.md)

## 介绍

本框架是一种针对数学公式解析的有效工具，能够通过C++的API解析包含嵌套函数，包含函数，数列步长累加等数学公式，返回值是一个数值的结果对象，同时也可以进行比较运算的操作，再进行比较的时候，返回值是一个布尔值结果对象。
如果您是一位 Java 或 python爱好者，可以专门前往 [JavaAPI](https://github.com/BeardedManZhao/mathematical-expression.git)
或 [PythonAPI](https://github.com/BeardedManZhao/mathematical-expression-Py) 中进行相关资料的查阅。

### 如何在 Windows 中使用库？

我们已经预编译好了 Windows 版本的DLL，在项目中有一个 include
文件目录，其中存储的就是库需要的所有头文件，您可以将其中的库文件导入到您的项目中，然后再集成本框架编译好的dll，下面是cmake的配置文件实例。

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

### 如何在 Linux 中使用库？

针对 Linux 系统的多样性，我们难以提供一种符合大部分系统架构的 dll
库文件，但是您无需担心，此库没有任何的第三方依赖，仅仅运行于本地库中，这对于它的源码编译工作来说是一个好消息，您可以访问我们写好的[《在 Linux 环境中编译 C++ 源码》](https://www.lingyuzhao.top/?/linkController=/articleController&link=76874815)
，根据文章的引导来进行编译工作。
当然，您也可以通过扫描二维码来阅读文章，这对于一些操作会更加简单。

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

- 类组件：ME::PrefixExpressionOperation
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

- 类组件：ME::BracketsCalculation2
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

### 区间累加表达式

- 类组件：ME::CumulativeCalculation
- 介绍

  在数学表达式中，往往有这样的一种公式，公式内容如下图所示，可以看到需要进行累加的数列操作，那么在这种公式的需求下，您可以通过上面的类组件去达到您所需要的目的。
  ![img_1](https://user-images.githubusercontent.com/113756063/201575828-5b76af88-6040-430d-a54c-61faf5905594.png)
- API使用示例

  语法层面于其他组件几乎一致，数学表达式的撰写于组件的计算示例就如下面所示，在这里展示的就是一个累加数学公式的计算。

```c++
#include "mathematical_expression.h"
int main() {
    system("chcp 65001");
    // 创建数学表达式解析库对象
    mathematical_expression me;
    // 获取一个计算累加数学表达式的组件
    ME::CumulativeCalculation cumulativeCalculation = me.getCumulativeCalculation();
    // 构建一个数学表达式，这里的"n[1,10,1]"就类似数学中的累加符号，n会在这个区间内不断增加，每增加一次都会被带入公式中计算一次
    // 其中[1,10,1]中的最后一个1 代表增加步长，能够实现区间内不同等差值的累加
    string s = "n[1,10,1] 2 * (n + 1)";
    // 检查数学表达式
    cumulativeCalculation.check(s);
    // 计算结果
    ME::CalculationNumberResults results = cumulativeCalculation << s;
    // 将结果打印出来
    cout << "计算层数：" << results.getResultLayers() << "\t计算结果：" << results << "\t计算来源：" << results.getCalculationSourceName() << endl;
}
```

- 运行结果

```
Active code page: 65001
计算层数：11    计算结果：130   计算来源：CumulativeCalculation

进程已结束,退出代码0
```

### 函数运算表达式

- 类组件：ME::FunctionFormulaCalculation
- 介绍

  针对一些函数的操作，在该框架中也有支持，可以使用上面的类进行这中需要函数的数学表达式的书写，需要注意的是，一切在表达式中使用到的函数都需要在“CalculationManagement”中进行逻辑注册，使得计算的时候可以访问到函数
- API使用示例

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

- 运行结果

```
Active code page: 65001
计算层数：1     计算结果：21    计算来源：BracketsCalculation

进程已结束,退出代码0
```

#### 注意事项

1.0.2 版本中 针对函数的注册操作不能向后兼容，如果是在1.0.2版本以以后的版本 请使用下面的方式注册函数

```c++
    // 准备函数 将函数的形参类型 由 double* 更改为 ME::MEStack<double> 即可 因为 ME::MEStack<double> 具有更大的灵活性
auto myFun =[](const ME::MEStack<double>& v) {
double res = 0;
for (int i = 0; i < v.size(); ++i){
res += v.get(i);
}
return res;
};
// 注册函数 将我们的函数注册成为 DoubleValue 的名称
ME::FunctionManager::append("sum", myFun);
```

### 函数多参数运算表达式

- 类组件：ME::FunctionFormulaCalculationTwo
- 介绍

针对一些在表达式中使用了函数的表达式计算，可以使用上面的类进行操作，它是“core.calculation.number.FunctionFormulaCalculation”类的升级版，从1.0.2版本开始出现，同时也是它的一个子类拓展实现。

相较于父类，本组件弥补了父类只能解析带有一个参数函数表达式的不足，在该组件中，可以使用很多的实参进行函数的运算，例如sum(
1,2,3) 这类函数，就是一个多参函数，接下来请看API的使用示例，在此示例中，展示了多惨函数表达式的计算与结果。

- API使用示例

```c++
#include <mathematical_expression.h>
#include "FunctionManager.h"
int main() {
    system("chcp 65001");
    // 准备函数 这里的函数的作用是将 3 个参数求和
    auto myFun = [](const ME::MEStack<double>& v) {
        double res = 0;
        for (int i = 0; i < v.size(); ++i){
            res += v.get(i);
        }
        return res;
    };
    // 注册函数 将我们的函数注册成为 DoubleValue 的名称
    ME::FunctionManager::append("sum", myFun);
    // 构建一个数学表达式，表达式中使用到了函数 DoubleValue
    string s = "2 * sum(2 + 3, 1 + 20, 10 + (1 - 2)) + 1";
    // 获取到 数学表达式解析库
    mathematical_expression me;
    // 获取到函数表达式计算组件
    auto functionFormulaCalculation = me.getFunctionFormulaCalculation2();
    // 检查数学表达式
    functionFormulaCalculation.check(s);
    // 计算出结果
    ME::CalculationNumberResults results = functionFormulaCalculation << s;
    // 将结果打印出来
    cout << "计算层数：" << results.getResultLayers() << "\t计算结果：" << results << "\t计算来源：" << results.getCalculationSourceName() << endl;
}
```

- 运行结果

```
Active code page: 65001
计算层数：1     计算结果：71    计算来源：BracketsCalculation

进程已结束,退出代码0
```

### 快速区间求和计算组件（基于括号表达式）

- 类组件：ME::FastSumOfIntervalsBrackets.py
- 介绍

  1.15版本的新产物，区间快速求和组件，是针对一个等差为1的区间进行所有元素求和的快速组件，它将一个区间在逻辑上模拟成为一个数学数列，并通过求和公式进行快速的求和。

  该组件实现了共享池计算功能，将检查，计算，以及上一次结果记录实现，能够加快计算速度，具体API调用如下所示。

```c++
#include "mathematical_expression.h"

int main() {
    system("chcp 65001");
    // 获取到数学表达式解析库对象
    mathematical_expression me;
    // 获取到区间累加表达式对象
    ME::FastSumOfIntervalsBrackets fastSumOfIntervalsBrackets = me.getFastSumOfIntervalsBrackets();
    // 准备需要被计算的数学表达式，这里的数学表达式中有个逗号，逗号两边代表的就是区间的两个边界
    string f1 = "1 + 10, 20 - (5 + 2)";
    // 检查数学表达式
    fastSumOfIntervalsBrackets.check(f1);
    // 将步长修改为 2
    fastSumOfIntervalsBrackets.step = 2;
    // 开始计算 并获取到结果对象
    ME::CalculationNumberResults r1 = fastSumOfIntervalsBrackets << f1;
    // 开始进行结果查看
    cout << "计算层数：" << r1.getResultLayers() << "\t计算结果：" << r1 << "\t计算来源：" << r1.getCalculationSourceName()
         << endl;
}
```

- 运行结果 从上面代码中我们可以看到，快速区间求和计算的公式由被逗号分割的两个括号表达式组成

```
Active code page: 65001
计算层数：1     计算结果：24    计算来源：FastSumOfIntervalsBrackets

进程已结束,退出代码0
```

### 数学函数表达式的注册与使用

```c++
#include <mathematical_expression.h>
#include "FunctionManager.h"
#include "ExpressionFunction.h"
#include "MEStack.h"

int main() {
    system("chcp 65001");
    // 这里的函数的作用是将 3 个参数求和
    // 注册函数 将我们的函数注册成为 DoubleValue 的名称
    ME::FunctionManager::append("sum(a,b,c) = a + b + c");
    // 构建一个数学表达式，表达式中使用到了函数 DoubleValue
    string s = "2 * sum(2 + 3, 1 + 20, 10 + (1 - 2)) + 1";

    // 获取到 数学表达式解析库
    mathematical_expression me;
    cout << "开始计算" << endl;

    // 获取到函数表达式计算组件
    auto functionFormulaCalculation = me.getFunctionFormulaCalculation2();
    // 检查数学表达式
    functionFormulaCalculation.check(s);
    // 计算出结果
    ME::CalculationNumberResults results = functionFormulaCalculation << s;
    // 将结果打印出来
    cout << "计算层数：" << results.getResultLayers() << "\t计算结果：" << results << "\t计算来源："
         << results.getCalculationSourceName() << endl;

    // 也可以手动获取到函数对象
    auto f = ME::FunctionManager::getFunction("sum");
    ME::MEStack<double> meStack;
    meStack.push(1);
    meStack.push(2);
    meStack.push(3);
    cout << f(meStack) << endl;
}
```

## C++API 特性

在 C++ 中，库具有更快的解析与计算速度，同时其具有更加庞大的功能，接下来针对C++中的特有功能来进行一个说明。

### 操作数之间的计算操作

通过计算组件计算出来的结果对象，其还具有运算功能，可以基于此方式来进行多个操作数之间的计算操作，接下来就是一个示例。

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
    // 使用结果对象进行计算
    ME::CalculationNumberResults res2 = res1 + res1;
    std::cout << "res1 + res1 = " << res2 << "\t其结果的源 = " << res2.getCalculationSourceName() << endl;
}
```

- 运行结果

```
1.0.1-mathematical_expression-C++
res1 + res1 = 24        其结果的源 = (BracketsCalculation + BracketsCalculation)

进程已结束,退出代码0
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
