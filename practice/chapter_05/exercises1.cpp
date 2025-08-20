// 5.1
// 编写一个要求用户输入两个整数的程序
// 该程序将计算并输出这两个整数之间(包括这两个整数)所有整数的和
// 这里假设先输入较小的整数
// 例如,如果用户输入的是2和9,则程序将指出2～9之间所有整数的和为44

#include <iostream>
int main()
{
    int num1;
    int num2;
    int sum = 0;

    std::cout << "输入第一个数: ";
    std::cin >> num1;

    std::cout << "输入第二个数: ";
    std::cin >> num2;

    if (num1 > num2)
    {
        // 从大到小循环，包含 num2
        for (int i = num1; i >= num2; i--)
        {
            sum += i;
        }
    }
    else // 包含 num1 < num2 和 num1 == num2 的情况
    {
        // 从小到大循环，包含 num2
        for (int i = num1; i <= num2; i++)
        {
            sum += i;
        }
    }

    std::cout << "两数之间的整数和为: " << sum << std::endl;
    return 0;
}