// 5.
// 编写模板函数max5()，它将一个包含5个T类型元素的数组作为参数，并返回数组中最大的元素(由于长度固定，因此可以在循环中使用硬编码，而不必通过参数来传递).在一个程序中使用该函数，将T替换为一个包含5个int值的数组和一个包含5个double值的数组，以测试该函数

#include <iostream>

const int ArSize = 5;

template <typename T>
T max5(const T arr[ArSize]);

int main()
{
    int arr[ArSize] = {172, 23, 9221, 577, 777};
    double ar[ArSize] = {23.33, 451.654, 56.543, 7.231, 111.111};

    int num1 = max5(arr);
    std::cout << "the num1 = " << num1 << std::endl;

    double num2 = max5(ar);
    std::cout << "the num2 = " << num2 << std::endl;

    return 0;
}

template <typename T>
T max5(const T arr[ArSize])
{
    T num = arr[0];
    for (int i = 1; i < ArSize; i++)
    {
        if (arr[i] > num)
        {
            num = arr[i];
        }
    }
    return num;
}