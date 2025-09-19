// 7.1
// 编写一个程序,不断要求用户输入两个数,直到其中的一个为0
// 对于每两个数,程序将使用一个函数来计算它们的调和平均数, 并将结果返回给 main(),而后者将报告结果
// 调和平均数指的是倒数平均值的倒数,计算公式如下:
// 调和平均数 = 2.0 * x * y / (x+y)

#include <iostream>
double average(double x, double y);

int main()
{
    double a, b;
    std::cout << "Enter two numbers (enter 0 for either to exit):" << std::endl;
    while (std::cin >> a >> b && a != 0 && b != 0)
    {
        double num = average(a, b);
        std::cout << num << std::endl;
        std::cout << "Enter two numbers (enter 0 for either to exit):" << std::endl;
    }
}

double average(double x, double y)
{
    if (x + y == 0)
    {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 0; // 或者返回一个特殊值
    }
    return (2.0 * x * y) / (x + y);
}