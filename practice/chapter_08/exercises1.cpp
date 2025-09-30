// 1.
// 编写通常接受一个参数（字符串的地址），并打印该字符串的函数。然而，如果提供了第二个参数（int类型），且该参数不为0，则该函数打印字符串的次数将为该函数被调用的次数（注意，字符串的打印次数不等于第二个参数的值，而等于函数被调用的次数）。
// 是的，这是一个非常可笑的函数，但它让您能够使用本章介绍的一些技术。在一个简单的程序中使用该函数，以演示该函数是如何工作的。

#include <iostream>
#include <string>
void show_string(const std::string& str, int flag = 0);

int main()
{
    std::string str = "apple iphone 17 Pro Max 1TB Vibrant Orange";
    show_string(str);
    show_string(str);
    show_string(str, 0);
    show_string(str, 1);
    show_string(str);
    show_string(str, 99);

    return 0;
}

void show_string(const std::string& str, int flag)
{
    static int count = 0;
    count++;
    if (0 == flag)
    {
        std::cout << "call show_string only once" << std::endl;
        std::cout << "the string = " << str << std::endl;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            std::cout << "the string = " << str << std::endl;
        }
    }
}