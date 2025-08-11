// 5. 假设要编写《C++ For Fools》一书。
// 请编写一个程序,输入全年的字符月份的销售量（图书数量,而不是销售额）
// 程序通过循环,使用初始化为月份名字的字符的char*数组（或string对象数组）逐月进行提示
// 并将输入的销售数据存储在一个int数组中
// 然后,程序将数据输出显示在屏幕上,并报告这一年的销售情况。

#include <iostream>
int main()
{
    std::string month[12] = {"Jan", "Feb", "Mar", "Apr",
                             "May", "Jun", "Jul", "Aug",
                             "Sep", "Oct", "Nov", "Dec"};
    int sum = 0;
    int number[12];
    for (int i = 0; i < 12; i++)
    {
        std::cout << month[i] << "  ";
        std::cin >> number[i];
        sum += number[i];
    }
    std::cout << sum << std::endl;
}