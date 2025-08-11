// 6. 完成编程练习5，但这一次使用一个二维数组来存储输入 —— 3年中每个月的销售量。
// 程序将报告每年销售情况以及三年的总销售量

#include <iostream>
int main()
{
    const int YEARS = 3;
    const int MONTHS = 12;

    int sales[YEARS][MONTHS];
    int total = 0;

    std::string Month[12] = {"Jan", "Feb", "Mar", "Apr",
                             "May", "Jun", "Jul", "Aug",
                             "Sep", "Oct", "Nov", "Dec"};

    for (int year = 0; year < YEARS; year++)
    {
        std::cout << "===== 输入第 " << year + 1 << " 年的销售量 =====" << std::endl;
        for (int month = 0; month < MONTHS; month++)
        {
            std::cout << "请输入 " << Month[month] << " 的销售量: ";
            std::cin >> sales[year][month];
        }
    }

    for (int i = 0; i < YEARS; i++)
    {
        int yearTotal = 0;
        for (int j = 0; j < MONTHS; j++)
        {
            // total += Month[i][j]; 这里有问题 Month[i][j]不是销售数额的二维数组
            yearTotal += sales[i][j];
        }
        total += yearTotal;
    }
    std::cout << "三年的总销售量: " << total << std::endl;
}