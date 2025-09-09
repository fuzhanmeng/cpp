// arrfun4.cpp -- function with an array range
#include <iostream>
const int ArSize = 8;
int sum_arr(const int* begin, const int* end);

int main()
{
    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};

    int sum = sum_arr(cookies, cookies + ArSize);
    std::cout << "total cookies eaten:  " << sum << std::endl;

    sum = sum_arr(cookies, cookies + 3);
    std::cout << "first three eaters ate " << sum << "cookies" << std::endl;

    sum = sum_arr(cookies + 4, cookies + 8);
    std::cout << "last four eaters ate " << sum << "cookies" << std::endl;

    return 0;
}

// return the sum of an integer array
int sum_arr(const int* begin, const int* end)
{
    const int* pt = nullptr;
    int total = 0;

    for (pt = begin; pt != end; pt++)
    {
        total = total + *pt;
    }
    return total;
}
