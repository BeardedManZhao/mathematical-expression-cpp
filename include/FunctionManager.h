//
// Created by zhao on 2023/6/22.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_FUNCTIONMANAGER_H
#define MATHEMATICAL_EXPRESSION_CPP_FUNCTIONMANAGER_H

#include "MEStack.h"

namespace ME {

    class FunctionManager {

    public:

        /**
         * 判断目前函数存储池中是否包含指定名称的函数对象。
         *
         * Determine whether the current function storage pool contains a Function object with the specified name.
         * @param name 需要被判断的函数的名称。
         *
         * The name of the function that needs to be evaluated.
         * @return 如果返回 true 代表期望的名称的函数已经注册到了函数缓冲池中。
         *
         * If true is returned, it indicates that the function with the expected name has already been registered in the function buffer pool.
         */
        static bool contain(const std::string &name);

        /**
         * 注册一个函数到函数库中，使得所有需要使用函数计算的组件都可以获取到函数对象的数据类型。
         * <p>
         * Register a function into the function library, so that all components that need to use the function calculation can obtain the data type of the function object.
         *
         * @param function 函数的表达式，您可以使用数学中的格式来定义一个函数，例如 f(x) = 2 * x
         *                 <p>
         *                 The expression of a function, you can use mathematical formats to define a function, such as f (x)=2 * x
         * @return 如果返回true 则代表函数注册操作成功!!!
         * <p>
         * If true is returned, the function registration operation is successful!!!
         * @throws WrongFormat 函数的格式发生错误则会抛出此异常
         */
        static void append(const std::string &fun);

        /**
         * 将一个函数添加添加到函数存储池中，相当于是进行的函数注册操作。
         *
         * Adding a function to the function storage pool is equivalent to registering a function.
         * @param name 需要被注册函数的名称。
         *
         * The name of the function that needs to be registered.
         * @param func 需要被注册的函数的实现。
         *
         * The implementation of the function that needs to be registered.
         * @param check 注册函数的时候是否要进行函数名称冲突的检查，这是一个默认为true的值，如果为 true 代表检查函数名称是否冲突。
         *
         * When registering a function, do you want to check for function name conflicts? This is a default value of true. If true, it means checking for function name conflicts.
         * @deprecated("此函数不应继续调用，请调用 append(const std::string &name, const std::function<double(ME::MEStack<double>)> &func, bool check = true); 相当于是函数的形参变为了 ME::MEStack<double>")
         */
        static void append(const std::string &name, const std::function<double(double[])> &func, bool check = true);

        /**
         * 将一个函数添加添加到函数存储池中，相当于是进行的函数注册操作。
         *
         * Adding a function to the function storage pool is equivalent to registering a function.
         * @param name 需要被注册函数的名称。
         *
         * The name of the function that needs to be registered.
         * @param func 需要被注册的函数的实现。
         *
         * The implementation of the function that needs to be registered.
         * @param check 注册函数的时候是否要进行函数名称冲突的检查，这是一个默认为true的值，如果为 true 代表检查函数名称是否冲突。
         *
         * When registering a function, do you want to check for function name conflicts? This is a default value of true. If true, it means checking for function name conflicts.
         */
        static void
        append(const std::string &name, const std::function<double(ME::MEStack<double>)> &func, bool check = true);

        /**
         * 从函数管理者中获取到指定名称的函数对象。
         *
         * Get the Function object with the specified name from the function manager.
         * @param name 被获取的函数的名称。
         *
         * The name of the function being obtained.
         * @return 指定函数名称对应的函数对象。
         *
         * Specifies the Function object corresponding to the function name.
         */
        static std::function<double(ME::MEStack<double>)> getFunction(const std::string &name);

    };
}


#endif //MATHEMATICAL_EXPRESSION_CPP_FUNCTIONMANAGER_H
