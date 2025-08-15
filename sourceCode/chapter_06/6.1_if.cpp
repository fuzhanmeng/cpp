//  if.cpp -- using the if statement

#include <iostream>
int main ()
{
    char ch;
    int space = 0;
    int total = 0;

    std::cin.get(ch);
    while ('.' != ch)
    {
        if (' ' == ch)
        {
            ++space;
        }
        ++total;    //  一共输入了多少个字符
        std::cin.get(ch);   //  逐个字符读取输入,包括所有字符(如字母、空格、换行符等)
    }
    
    std::cout << space << " space, " << total;
    std::cout << " characters total in sentence\n";

    return 0;
}