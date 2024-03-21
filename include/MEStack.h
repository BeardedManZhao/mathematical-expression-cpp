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

        /**
         * 将栈中指定索引处的元素获取到，同时不影响栈中所有的元素
         * @param index 需要获取的元素的位置
         * @return 元素的具体数值
         */
        T get(size_t index) const;

        /**
         * 将栈中的栈顶元素直接取出，此操作将会删除栈顶元素，并将栈顶元素获取到。
         * @return 被成功删除的栈顶的元素。
         */
        T pop_get();
    };

    template<typename T>
    T MEStack<T>::get(size_t index) const {
        return this->c[index];
    }

    template<typename T>
    T MEStack<T>::pop_get() {
        T v = this->top();
        this->pop();
        return v;
    }


} // ME

#endif //MATHEMATICAL_EXPRESSION_CPP_MESTACK_H
