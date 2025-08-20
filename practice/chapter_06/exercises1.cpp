// 1.
// 编写一个程序,该取键盘输入,直到遇到 @ 符号为止,并回显输入(数字除外),同时将大写字符转换为小写,将小写字符转换为大写(别忘了 cctype 标准系列).

#include <iostream>
#include <cctype>

int main()
{
    char ch;
    std::cout << "enter ch in while" << std::endl;

    while (std::cin.get(ch) && '@' != ch)
    {
        if (isdigit(ch))
        {
        }
        else if (islower(ch))
        {
            ch = toupper(ch);
            std::cout << ch;
        }
        else if (isupper(ch))
        {
            ch = tolower(ch);
            std::cout << ch;
        }
        else
            std::cout << ch;
    }

    return 0;
}