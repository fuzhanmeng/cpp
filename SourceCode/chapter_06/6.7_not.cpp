// not.cpp --using the not operator

#include <iostream>
#include <climits>
#include <type_traits>

//  检查指定变量的类型是否是整数
bool is_int(double x)
{
    if (x <= INT_MAX && x >= INT_MIN)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    double num;

    std::cout << "Yo, dude! Enter an integer value: ";
    std::cin >> num;

    while (!is_int(num))
    {
        std::cout << "out of range -- replease try again: ";
        std::cin >> num;
    }
    int val = int(num);
    std::cout << "you've entered the integer " << val << "\nBye\n";

    return 0;
}
