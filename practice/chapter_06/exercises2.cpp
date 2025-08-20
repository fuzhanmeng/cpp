// 2.
// 编写一个程序,最多将 10 个 donation 值读入到一个double数组中(如果您愿意,也可使用模板 `array`).
// 程序到达文件尾时终止数组输入,并报告这些数字的平均值以及数组中有多少个数字大于平均值.

#include <iostream>
#include <array>

int main()
{
    std::array<double, 10> donation;
    int sum = 0;
    int count = 0;
    int num = 0;
    int average = 0;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "enter an number: " << std::endl;
        std::cin >> donation[i];
        if (donation[i] == EOF)
        {
            break;
        }
        else
        {
            sum += donation[i];
            count++;
        }
        std::cout << "the count is " << count << std::endl;
        average = sum / count;
    }

    for (int i = 0; i < count; i++)
    {
        if (donation[i] > average)
        {
            num++;
        }
    }

    std::cout << "averange is " << average << " and > averange numbers is " << num << std::endl;
}