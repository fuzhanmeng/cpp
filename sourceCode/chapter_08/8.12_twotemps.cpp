// twotemps.cpp -- using overloaded template functions

#include <iostream>

template <typename T>
void Swap(T& a, T& b);

template <typename T>
void Swap(T* a, T* b, int n);

void show(int* a);
const int Lim = 8;

int main()
{
    int i = 10;
    int j = 20;

    std::cout << "i = " << i << ", j = " << j << std::endl;
    std::cout << "using compiler-generated int swapper: \n";
    Swap(i, j);
    std::cout << "now i = " << i << ", j = " << j << std::endl;

    int d1[Lim] = {0, 7, 0, 4, 1, 7, 7, 6};
    int d2[Lim] = {0, 7, 2, 0, 1, 9, 6, 9};
    std::cout << "Original arrays: \n";
    show(d1);
    show(d2);
    Swap(d1, d2, Lim);

    std::cout << "after swap d1 and d2 \n";
    show(d1);
    show(d2);

    return 0;
}

template <typename T>
void Swap(T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T>
void Swap(T* a, T* b, int n)
{
    T temp;
    for (int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void show(int* a)
{
    std::cout << a[0] << a[1] << "/";
    std::cout << a[2] << a[3] << "/";
    for (int i = 4; i < Lim; i++)
    {
        std::cout << a[i];
    }
    std::cout << std::endl;
}