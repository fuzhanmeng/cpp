// arrfun2.cpp -- functions with an array argument

#include <iostream>
int sum_arr(int* arr, int n);
const int ArSize = 8;

int main()
{
    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};

    std::cout << cookies << " = array address,  ";
    // cookies is an array (type int[8]) sizeof cookies = 8 * 4 = 32
    std::cout << sizeof cookies << " = sizeof cookies" << std::endl;

    int sum = sum_arr(cookies, ArSize);
    std::cout << "total cookies eaten: " << sum << std::endl;

    sum = sum_arr(cookies, 3);
    std::cout << "first three eaters ate " << sum << " cookies" << std::endl;

    sum = sum_arr(cookies + 4, 4);
    std::cout << "last four eaters ate " << sum << " cookies" << std::endl;

    return 0;
}

int sum_arr(int* arr, int n)
{
    int total = 0;
    std::cout << arr << " = arr, ";

    // arr is a pointer (type int*) sizeof arr = 8
    std::cout << sizeof arr << " = sizeof arr" << std::endl;

    for (int i = 0; i < n; i++)
    {
        total = total + arr[i];
    }

    return total;
}
