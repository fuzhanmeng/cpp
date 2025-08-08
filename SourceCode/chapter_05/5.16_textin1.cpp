// textin1.cpp -- reading chars with a while loop

#include <iostream>

int main ()
{
    char ch;
    int count = 0;
    std::cout << "enter characters; enter # to quit" << std::endl;
    std::cin >> ch; //std::cin >> ch只能存储​​单个字符​​ 跳过​​所有空白字符
    while ('#' != ch)
    {
        std::cout << ch << std::endl;
        count++;
        std::cin >> ch;
    }
    
    std::cout <<  count << std::endl;
    return 0;
}