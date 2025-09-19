// 8.在不使用array类的情况下完成程序清单7.15所做的工作。编写两个这样的版本:
// a.使用const char*数组存储表示季度名称的字符串，并使用double数组存储开支。
// b.使用const
// char*数组存储表示季度名称的字符串，并使用一个结构，该结构只有一个成员——一个用于存储开支的double数组。这种设计与使用array类的基本设计类似。

#include <iostream>

const int Seasons = 4;
const char* seasonNames[Seasons] = {"Spring", "Summer", "Fall", "Winter"};

void fill_array(double* ar, int n);
void show_array(const double* ar, int n);

int main()
{
    double expenses[Seasons];
    fill_array(expenses, Seasons);
    show_array(expenses, Seasons);
    return 0;
}

void fill_array(double* ar, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "Enter " << seasonNames[i] << " expenses: ";
        std::cin >> ar[i];
    }
}

void show_array(const double* ar, int n)
{
    double total = 0;
    std::cout << "\nEXPENSES:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << seasonNames[i] << " expenses = " << ar[i] << std::endl;
        total += ar[i];
    }
    std::cout << "Total expenses = " << total << std::endl;
}
