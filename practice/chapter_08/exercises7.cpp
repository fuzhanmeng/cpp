// 7.
// 修改程序清单8.14，使其使用两个名为SumArray()的模板函数来返回数组元素的总和，而不是显示数组的内容。程序应显示thing的总和以及所有debt的总和。

#include <iostream>

struct debts
{
    char name[20];
    double amount;
};

// 普通数组模板：用于 int, double 等基本类型
template<typename T>
T SumArray(T arr[], int n)
{
    T sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

// debts 数组专用函数（非模板，直接处理 amount 成员）
double SumArray(debts arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i].amount;
    return sum;
}

int main()
{
    int things[6] = {13, 31, 103, 301, 310, 130};
    debts mr_E[3] =
    {
        {"Ima Wolfe", 2400.0},
        {"Ura Foxe", 1300.0},
        {"Iby Stout", 1800.0}
    };

    int sumthings = SumArray(things, 6);
    double sumdebt = SumArray(mr_E, 3);

    std::cout << "The sum of things: " << sumthings << std::endl;
    std::cout << "The sum of debts: " << sumdebt << std::endl;

    return 0;
}
