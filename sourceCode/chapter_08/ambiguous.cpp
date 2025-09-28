// test.cpp

#include <iostream>
template <typename T>
T my_test(T a, T b);

template <typename T>
void g(T a, T b);

template <typename T>
void g(T& a, T& b);

template <typename T>
void g(T* a, T* b);

int main()
{
    std::cout << "my_test(1, 2)" << my_test(1, 2) << std::endl;
    std::cout << "my_test(2.11, 9.24)" << my_test(2.11, 9.24) << std::endl;

    int a = 1, b = 2;

    // 1.void g(T a, T b) 2. void g(T& a, T& b)
    // g(a, b);
    g(&a, &b);
}

template <typename T>
T my_test(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
void g(T a, T b)
{
    std::cout << "g(T a, T b)" << std::endl;
}

template <typename T>
void g(T& a, T& b)
{
    std::cout << "g(T& a, T& b)" << std::endl;
}

template <typename T>
void g(T* a, T* b)
{
    std::cout << "g(T* a, T* b)" << std::endl;
}
