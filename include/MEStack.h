//
// Created by Liming on 2023/6/19.
//

#ifndef MATHEMATICAL_EXPRESSION_CPP_MESTACK_H
#define MATHEMATICAL_EXPRESSION_CPP_MESTACK_H

#include <stack>
#include "iostream"

namespace ME {

    /**
     * 自定义的栈数据结构
     * @tparam T 栈中的每一个元素类型
     */
    template<typename T>
    class MEStack : public std::stack<T> {

        friend
        std::ostream &operator<<(std::ostream &out, const MEStack<int> &meStack);

        friend
        std::ostream &operator<<(std::ostream &out, const MEStack<double> &meStack);

        friend
        std::ostream &operator<<(std::ostream &out, const MEStack<char> &meStack);

        friend
        std::ostream &operator<<(std::ostream &out, const MEStack<std::string> &meStack);

    public:
        T get(int index);
    };

    template<typename T>
    T MEStack<T>::get(int index) {
        return this->c[index];
    }


} // ME

#endif //MATHEMATICAL_EXPRESSION_CPP_MESTACK_H
