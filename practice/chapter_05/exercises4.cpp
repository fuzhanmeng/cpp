// 5.4
// Daphne以10%的单利投资了100美元.也就是说,每一年的利润都是投资额的10%,即每年10美元.
// 而Cleo以5%的复利投资了100美元.也就是说,利息是当前存款(包括获得的利息)的5%,
// Cleo在第一年投资100美元的盈利是5%—得到了105美元.下一年的盈利是105美元的5%—即5.25美元,
// 依此类推.请编写一个程序,计算多少年后,
// Cleo的投资价值才能超过Daphne的投资价值,并显示此时两个人的投资价值.
#include <iostream>
#include <iomanip> // 用于格式化输出

int main()
{
    double Daphne = 100.0;
    double Cleo = 100.0;

    int year = 0; // 从第0年开始

    // 当Cleo小于或等于Daphne时继续循环
    while (Cleo <= Daphne)
    {
        year++; // 年份增加

        // 计算当前年度的投资价值
        Daphne = 100.0 + 10 * year; // 单利公式
        Cleo = Cleo * 1.05;         // 复利公式
    }

    // 输出结果
    std::cout << "After " << year << " years, Cleo's investment exceeds Daphne's." << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Daphne's balance: $" << Daphne << std::endl;
    std::cout << "Cleo's balance: $" << Cleo << std::endl;

    return 0;
}