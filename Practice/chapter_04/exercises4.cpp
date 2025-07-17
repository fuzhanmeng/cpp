// 4.

//  编写一个程序，它要求用户首先输入其名，再输入其姓；然后程序使用一个逗号和空格将姓名组合起来，并存储和显示组合结果。请使用 string 对象和头文件 string 中的函数。下面是该程序运行时的情形：
//  Enter your first name: Flip
//  Enter your last name: Fleming
//  Here’s the information in a single string: Fleming, Flip

#include <iostream>
#include <string>

int main()
{
    std::string first_name;
    std::string last_name;

    std::cout << "Enter your first name:";
    std::getline(std::cin, first_name);

    std::cout << "Enter your last name:";
    std::getline(std::cin, last_name);

    std::cout << "Here’s the information in a single string:" << first_name << ", " << last_name << std::endl;

    return 0;
}