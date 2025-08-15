// condition.cpp -- using the conditioanl operator

#include <iostream>
int main()
{
    int a, b;
    std::cout << "Enter two integers: ";
    std::cin >> a >> b;
    std::cout << "the larger of " << a << " and " << b;
    int c = a > b ? a : b;  // if a > b  c = a else c = b
    std::cout << " is " << c << std::endl;

    return 0;
}