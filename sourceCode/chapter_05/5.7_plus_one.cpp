// plus_one.cpp -- the increment operator

#include <iostream>
int main ()
{
    int a = 10;
    int b = 20;

    std::cout << "a = " << a << ":  b = " << b << std::endl;
    std::cout << "a++ = " << a++ << ": ++b = " << ++b << std::endl;
    std::cout << "a = " << a << ": b = " << b << std::endl;

    int x = 5;
    int y = x++;
    std::cout << "y = " << y << "  x = " << x << std::endl;

    int z = 5;
    int m = ++z;
    std::cout << "m = " << m << "  z = " << z << std::endl; 

    return 0;
}