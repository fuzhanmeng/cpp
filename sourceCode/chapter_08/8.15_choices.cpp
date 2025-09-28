// choices.cpp -- choosing a template

#include <iostream>
#include <ostream>

template <typename T>
T lesser(T a, T b)
{
    std::cout << "template A" << std::endl;
    return a > b ? a : b;
}

template <typename T>
T lesser(int a, int b)
{
    std::cout << "template B" << std::endl;
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    return a < b ? a : b;
}

int main()
{
    int m = 20, n = -30;
    double x = 15.5, y = 25.9;

    std::cout << lesser(m, n) << std::endl;      // 模板 A（B 不能推导返回类型）
    std::cout << lesser(x, y) << std::endl;      // 模板 A（double）
    std::cout << lesser<>(m, n) << std::endl;    // 模板 A（强制模板推导，只能选 A）
    std::cout << lesser<int>(x, y) << std::endl; // 模板 B（显式指定 T，匹配成功，优先 B）

    // std::cout << lesser(m, x) << std::endl; -- error m->int x->double

    return 0;
}