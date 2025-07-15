#include <iostream>
#include <cstring>

int main()
{
    char charr[20];
    std::string str;

    // charr 中的内容是未定义的随机内存值
    std::cout << "Length of string in charr before input: " << strlen(charr) << std::endl;
    std::cout << "Length of string in str before input: " << str.size() << std::endl;

    std::cout << "Enter a line of text: " << std::endl;

    // indicate maximum length 从输入读取最多 19 字符到 charr 换行符 \n 和最后一个字符 0 还在输入缓冲区
    std::cin.getline(charr, 20); 
    std::cout << "You entered: " << charr << std::endl;
    
    std::cout << "Enter another line of text: " << std::endl;
    std::getline(std::cin, str); 

    std::cout << "You entered: " << str << std::endl;
    std::cout << "Length of string in charr after input: "
              << strlen(charr) << std::endl;
    std::cout << "Length of string in str after input: "
              << str.size() << std::endl;
    
    return 0;
}