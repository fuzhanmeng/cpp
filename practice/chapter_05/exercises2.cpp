// 5.2
// 使用array对象(而不是数组)和long double(而不是long long)
// 重新编写程序清单5.4，并计算100的阶乘。

#include <iostream>
#include <array>

const int ArSize = 101;

int main()
{
    std::array<long double, ArSize> Array;
    Array[0] = Array[1] = 1LL;

    for (int i = 2; i < ArSize; i++)
    {
        Array[i] = i * Array[i - 1];
    }

    for (int i = 0; i < ArSize; i++)
    {
        std::cout << i << "的阶乘是" << Array[i] << std::endl;
    }

    return 0;
}