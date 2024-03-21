//
// Created by zhao on 2023/6/22.
//

#include <string>
#include <unordered_map>
#include <functional>
#include "FunctionManager.h"
#include "MExceptional.h"
#include "ExpressionFunction.h"


/**
 * 执行函数存储表
 */
std::unordered_map<std::string, const std::function<double(ME::MEStack<double>)>> functions;

/**
 * 表达式函数存储表
 */
std::unordered_map<string, const ME::ExpressionFunction> e_functions;

void ME::FunctionManager::append(const std::string &name, const std::function<double(ME::MEStack<double>)> &func,
                                 bool check) {
    auto f = functions.find(name);
    if (check && f != functions.end()) {
        // 代表已经存在
        std::string data = "目标函数已经被注册了，如果您希望覆盖旧的同名函数请将第二个形参设置为false，否则您就必须将新函数的名称更改。\nThe target function has already been registered. If you want to overwrite the old function with the same name, please set the second parameter to false, otherwise you will have to change the name of the new function.\n";
        data.append("Conflicting function names = ").append(name);
        throw ME::MExceptional(data);
    }
    // 开始注册函数
    functions.insert(std::make_pair(name, func));
}

bool ME::FunctionManager::contain(const std::string &name) {
    return functions.find(name) != functions.end() && e_functions.find(name) != e_functions.end();
}

std::function<double(ME::MEStack<double>)> ME::FunctionManager::getFunction(const std::string &name) {
    if (functions.find(name) != functions.end()) {
        return functions.at(name);
    } else {
        return e_functions.at(name);
    }
}

void ME::FunctionManager::append(const std::string &name, const std::function<double(double *)> &func, bool check) {
    throw AbnormalOperation(
            "从 1.0.2 版本开始 您注册函数的时候，请将函数的形参类型 从 double* 更换为 ME::MEStack<double>，新的形参具有更多的操作可以使用，非常方便！\nStarting from version 1.0.2, when registering functions, please change the parameter type of the function from double * to ME:: MEStack<double>. The new parameter has more operations to use, which is very convenient!");
}

void ME::FunctionManager::append(const std::string &fun) {
    ME::ExpressionFunction f = ExpressionFunction::parse(fun);
    cout << "zhao: " << f.getName() << endl;
    e_functions.insert(std::make_pair(f.getName(), f));
}