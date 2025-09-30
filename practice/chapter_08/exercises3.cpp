// 3.
// 编写一个函数，它接受一个指向string对象的引用作为参数，并将该string对象的内容转换为大写，为此可使用表6.4描述的函数toupper()然后编写一个程序，它通过使用一个循环让您能够用不同的输入来测试这个函数，该程序的运行情况如下:

//  Enter a string (q to quit): go away
//  GO AWAY
//  Next string (q to quit): good grief!
//  GOOD GRIEF!
//  Next string (q to quit): q
//  Bye.

#include <cctype>
#include <iostream>
#include <string>

void chang(std::string& str);

int main()
{
    std::string str;
    std::cout << "Enter a string (q to quit): ";
    while (std::getline(std::cin, str))
    {
        if (str == "q")
        {
            std::cout << "Bye" << std::endl;
            break;
        }
        else
        {
            chang(str);
            std::cout << "Next string (q to quit): ";
        }
    }

    return 0;
}

void chang(std::string& str)
{
    for (char& ch : str)
    {
        ch = std::toupper(static_cast<char>(ch));
        std::cout << ch;
    }
    std::cout << std::endl;
}
