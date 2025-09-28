// funtemp.cpp -- using a function template
#include <iostream>

// function template prototype
template <typename T>
void Swap(T& a, T& b);

int main()
{
    int i = 10;
    int j = 20;

    std::cout << "i = " << i << ", j = " << j << std::endl;
    std::cout << "using compiler-generated int swapper: \n";
    Swap(i, j);
    std::cout << "now i = " << i << ", j = " << j << std::endl;

    double x = 24.5;
    double y = 81.7;

    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "using compiler-generated int swapper: \n";
    Swap(x, y);
    std::cout << "now x = " << x << ", y = " << y << std::endl;

    return 0;
}

// function template definition
template <typename T> // or class T
void Swap(T& a, T& b)
{
    T temp; // temp a variable of type T
    temp = a;
    a = b;
    b = temp;
}