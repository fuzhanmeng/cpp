// newplace.cpp -- using placement new
#include <iostream>

const int BUF = 512;
const int N = 5;
char buffer[BUF];

int main()
{
    double *pd1, *pd2;
    int i;

    std::cout << "calling new and placement new:\n";
    pd1 = new double[N];          // use heap
    pd2 = new (buffer) double[N]; // use buffer array

    for (int i = 0; i < N; i++)
    {
        pd2[i] = pd1[i] = 1000 + 20.0 * i;
    }
    std::cout << "memory addresses:\n"
              << "  heap: " << pd1 << "  static: " << (void *)buffer << std::endl;

    std::cout << "memory contents:\n";

    for (int i = 0; i < N; i++)
    {
        std::cout << pd1[i] << " at " << &pd1[i] << "; ";
        std::cout << pd2[i] << " at " << &pd2[i] << std::endl;
    }

    std::cout << "\ncalling new and placement new a third time:\n";

    double *pd3, *pd4;
    pd3 = new double[N];          // find new address
    pd4 = new (buffer) double[N]; // overwrite old data

    for (int i = 0; i < N; i++)
    {
        pd4[i] = pd3[i] = 1000 + 40.0 * i;
    }

    std::cout << "memory contents:\n";

    for (int i = 0; i < N; i++)
    {
        std::cout << pd3[i] << " at " << &pd3[i] << "; ";
        std::cout << pd4[i] << " at " << &pd4[i] << std::endl;
    }

    std::cout << "\nCalling new and placement new a third time:\n";
    delete[] pd1;
    pd1 = new double[N];
    pd2 = new (buffer + N * sizeof(double)) double[N];

    for (int i = 0; i < N; i++)
    {
        pd2[i] = pd1[i] = 1000 + 60 * i;
    }
    std::cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        std::cout << pd1[i] << " at " << &pd1[i] << "; ";
        std::cout << pd2[i] << " at " << &pd2[i] << std::endl;
    }
    delete[] pd1;
    delete[] pd3;
    return 0;
}