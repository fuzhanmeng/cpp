//  or.cpp  -- using the logical or operator

#include <iostream>
int main ()
{
    std::cout << "this program may reformat your hard disk" << std::endl;
    std::cout << "and destroy all your data" << std::endl;
    std::cout << "do you wish to continue? <y/n> " << std::endl;

    char ch;
    std::cin >> ch;

    if ('y' == ch || 'Y' == ch)
    {
        // \a是一个转义序列，代表​​警报字符（alert）​​ 连续两个 \a会发出两次蜂鸣声
        std::cout << "you were warned!\a\a\n";
    } else if('n' == ch || 'N' == ch)
    {
        std::cout << "A wise choice ... bye" << std::endl;
    }
    else
    {
        std::cout << "that wasn't a y or n! Apparently you "
                     "can't follow\n =ninstructions, so "
                     "I'll trash your disk anyway. \a\a\a\n";
    }
    return 0;
}