// strtype4.cpp -- line input

#include <iostream>
#include <string>  // make string class available
#include <cstring> // C-style string library

int main()
{
    char charr[20];
    std::string str;

    std::cout << "Length of string in charr before input: " << strlen(charr) << std::endl;
    //  charr[20] 未初始化  所以 strlen获取的到长度不一定是多少
    std::cout << "Length of string in str before input: " << str.size() << std::endl;

    std::cout << "Enter a line of text: " << std::endl;
    std::cin.getline(charr, 20); // indicate maximum length 从输入读取最多 19 字符到 charr
    std::cout << "You entered: " << charr << std::endl;

    std::cout << "Enter another line of text: " << std::endl;
    std::getline(std::cin, str); // cin now an argument; no length specifier

    std::cout << "You entered: " << str << std::endl;
    std::cout << "Length of string in charr after input: "
              << strlen(charr) << std::endl;
    std::cout << "Length of string in str after input: "
              << str.size() << std::endl;

    return 0;
}