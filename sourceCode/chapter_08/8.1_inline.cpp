// inline.cpp -- using an inline function

#include <iostream>

// an inline function definition
inline double square(double x) {return  x * x;}

int main()
{
    double a, b;
    double c = 13;

    a = square(5);
    b = square(4.5 + 7.5);

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "c squared = " << square(c++) << std::endl;
    std::cout << "now c =" << c << std::endl;

    return 0;
}