//  cctypes.cpp -- using the ctype.h library

#include <iostream>
#include <cctype>

int main()
{
    std::cout << "Enter text for analusis, and type @ "
              << " to  terminate input. \n";

    char ch;
    int whitespace = 0;
    int digits = 0;
    int chars = 0;
    int punct = 0;
    int others = 0;

    std::cin.get(ch);
    while ('@' != ch)
    {
        if (isalpha(ch)) //  检查字符是否是字母
        {
            chars++;
        }
        else if (isspace(ch)) //  检查字符是否是空白字符
        {
            whitespace++;
        }
        else if (isdigit(ch)) //  检查字符是否是十进制数字
        {
            digits++;
        }
        else if (ispunct(ch)) //  检查字符是否是标点符号
        {
            punct++;
        }
        else
            others++; //  不属于以上任何类别的字符（如控制字符、非ASCII字符等）
        std::cin.get(ch);
    }

    std::cout << chars << " letters, "
              << whitespace << " whitespace, "
              << digits << " digits, "
              << punct << " punct, "
              << others << " others. \n";

    return 0;
}