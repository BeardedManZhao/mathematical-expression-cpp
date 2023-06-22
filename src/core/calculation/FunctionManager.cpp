//
// Created by zhao on 2023/6/22.
//

#include <string>
#include <unordered_map>
#include <functional>
#include "FunctionManager.h"
#include "MExceptional.h"

std::unordered_map<std::string, const std::function<double(double[])>> functions;

void ME::FunctionManager::append(const std::string &name, const std::function<double(double [])> &func, bool check) {
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
    return functions.find(name) != functions.end();
}

std::function<double(double[])> ME::FunctionManager::getFunction(const std::string &name) {
    return functions.at(name);
}
