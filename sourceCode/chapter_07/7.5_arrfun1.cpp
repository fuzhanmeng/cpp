// arrfun1.cpp -- functions with an array argumet

#include <iostream>
const int ArSize = 8;
// int sum_arr(int arr[], int n);
int sum_arr(int* ar, int n);

int main()
{
    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};

    int sum = sum_arr(cookies, ArSize);

    std::cout << "the sum is  " << sum << std::endl;

    return 0;
}

// return the sum of an integer array
int sum_arr(int* ar, int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total = total + ar[i];
    }
    return total;
}
