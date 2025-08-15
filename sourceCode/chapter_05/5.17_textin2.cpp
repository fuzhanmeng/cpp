// textin2.cpp -- using cin.get(char)

#include <iostream>
int main ()
{
    char ch;
    int count = 0;
     
    std::cout << "enter  characters; enter # to quit: " << std::endl;
    std::cin.get(ch);   //读取​​所有字符，包括空白符 输入的回车（\n）也被读取并输出为换行

    while ('#' != ch)
    {
        std::cout << ch;
        count++;
        std::cin.get(ch);
    }
    
    std::cout << count << std::endl;

    return 0;
}