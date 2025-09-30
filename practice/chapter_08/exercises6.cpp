// 6.
// 编写模板函数maxn(),它将由一个T类型元素组成的数组和一个表示数组元素数目的整数作为参数，并返回数组中最大的元素。
// 在程序对它进行测试，该程序使用一个包含6个int元素的数组和一个包含4个double元素的数组来调用该函数。
// 程序还包含一个具体化，它将char指针数组和数组中的指针数量作为参数，并返回最长的字符串的地址。
// 如果有多个这样的字符串，则返回其中第一个字符串的地址。使用由5个字符串指针组成的数组来测试该具体化。

#include <cstring>
#include <iostream>

template <typename T>
T maxn(T arr[], int n);

template <>
char* maxn<char*>(char* arr[], int n);

int main()
{
    int intArr[6] = {3, 7, 2, 9, 5, 1};
    std::cout << "Max int: " << maxn(intArr, 6) << std::endl;

    double doubleArr[4] = {3.5, 2.1, 7.8, 4.6};
    std::cout << "Max double: " << maxn(doubleArr, 4) << std::endl;

    char* strArr[5] = {"apple", "banana", "kiwi", "strawberry", "pear"};
    std::cout << "Longest string: " << maxn(strArr, 5) << std::endl;

    return 0;
}

template <typename T>
T maxn(T arr[], int n)
{
    std::cout << "template A " << std::endl;
    T maxVal = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

template <>
char* maxn<char*>(char* arr[], int n)
{
    std::cout << "template B " << std::endl;
    int maxLen = 0;
    for (int i = 0; i < n; i++) 
    {
        if (std::strlen(arr[maxLen]) < std::strlen(arr[i])) 
        {
            maxLen = i;
        }
    }

    return arr[maxLen];
}
