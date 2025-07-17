// 3.

//  编写一个程序，它要求用户首先输入其名，然后输入其姓；然后程序使用一个逗号和空格将姓名组合起来，并存储和显示组合结果。请使用 char 数组和头文件 cstring 中的函数。下面是该程序运行时的情形：
//  Enter your first name: Flip
//  Enter your last name: Fleming
//  Here’s the information in a single string: Fleming, Flip

#include <iostream>
#include <cstring>

int main()
{
    char first_name[20];
    char last_name[20];
    char full_name[20];

    std::cout << "Enter your first name:";
    std::cin.getline(first_name, 20);

    std::cout << "Enter your last name:";
    std::cin.getline(last_name, 20);

    strcpy(full_name, first_name);
    strcat(full_name, ", ");
    strcat(full_name, last_name);

    std::cout << "Here's the information in a single string: " << full_name << std::endl;

    return 0;
}