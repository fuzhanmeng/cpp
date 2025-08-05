//  ppinter_arithmetic.cpp 

#include <iostream>

int main ()
{
    double arr[5] = {12.3, 44.2, 67.5, 22, 112.22};
    double* pt = arr;

    std::cout << "*pt = " << *pt << std::endl;
    std::cout << "*pt++ = " << *pt++ << std::endl; // 12.3
    std::cout << "*++pt = " << *++pt << std::endl; // 67.5
    std::cout << "++*pt = " << ++*pt << std::endl; // 68.5
    std::cout << "(*pt)++ = " << (*pt)++ << std::endl; // 69.5  此时pt指向了67.5 不是之前的68.5
    std::cout << "*pt = " << *pt << std::endl; // 69.5
    return 0;
}