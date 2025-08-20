// 5.3
// 编写一个要求用户输入数字的程序.每次输入后,程序将报告到目前为止所有输入的累计和
// 当用户输入0时，程序结束。

#include <iostream>

int main()
{
    std::cout << "enter sum number: ";
    int num;
    int sum = 0;
    do
    {
        std::cin >> num;
        // sum = sum + num;
        sum += num;
        std::cout << sum << std::endl;
    } while (num != 0);
    return 0;
}