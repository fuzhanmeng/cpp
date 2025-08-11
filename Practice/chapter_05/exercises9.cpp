// 5.9
// 编写一个满足前一个练习中描述的程序,但使用 string 对象而不是字符数组
// 请在程序中包含头文件 string,并使用关系运算符来进行 比较测试

#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter words (to stop, type the word done): " << std::endl;

    std::string str;
    std::getline(std::cin, str);
    int sum = 0;

    while (str != "done")
    {
        std::getline(std::cin, str);
        sum++;
    }
    std::cout << "You entered a total of " << sum << " words." << std::endl;
}