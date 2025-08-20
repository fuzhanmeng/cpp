// 5.
// 在 Neutronia 王国,货币单位是 tvarp,收入所得税的计算方式如下：

// - 第一个 5000 tvarps：不收税
// - 接下来的 10000 tvarps：收税 10%
// - 接下来的 20000 tvarps：收税 15%
// - 超过 35000 tvarps 的部分：收税 20%

// 例如,收入为 38000 tvarps 时,所得税为：

// 5000 × 0.00 + 10000 × 0.10 + 20000 × 0.15 + 3000 × 0.20 = 4600 tvarps

// 请编写一个程序,使用循环让用户输入收入,并报告应缴税金.当用户输入负数或非数字字符时,循环结束.

#include <iostream>
#include <cctype>

int main()
{
    int tvarps;
    std::cout << "cin your tvarps: ";
    double tax = 0;
    std::cin >> tvarps;

    while (tvarps >= 0 && !isdigit(tvarps))
    {
        double tax = 0.0;
        // (0 < tvarps)结果是布尔值（0 或 1），然后与 5000 比较
        if (tvarps <= 5000)
        {
            tax = 0;
        }
        else if (tvarps <= 15000)
        {
            tax = (tvarps - 5000) * 0.1;
        }
        else if (tvarps <= 35000)
        {
            tax = (10000 * 0.1) + ((tvarps - 15000) * 0.15);
        }
        else if (tvarps > 35000)
        {
            tax = (10000 * 0.10) + (20000 * 0.15) + ((tvarps - 35000) * 0.20);
        }

        std::cout << "taxation = " << tax << " tveaps" << std::endl;
        std::cout << "cin your tvarps: ";
        std::cin >> tvarps;
    }
}