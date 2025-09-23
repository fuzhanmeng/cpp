// swaps.cpp -- swapping with reference and with pointers

#include <iostream>
void swapr(int& a, int& b); // a,b are aliases for ints
void swapp(int* a, int* b); // a,b are addresses of ints
void swapv(int a, int b);   // a,b are new variables

int main()
{
    int wallet1 = 300;
    int wallet2 = 350;

    std::cout << "wallet1 = " << wallet1 << " $" << std::endl;
    std::cout << "wallet2 = " << wallet2 << " $" << std::endl;

    std::cout << "using reference to swap contents: \n";
    swapr(wallet1, wallet2);
    std::cout << "wallet1 = " << wallet1 << " $" << std::endl;
    std::cout << "wallet2 = " << wallet2 << " $" << std::endl;

    std::cout << "using pointers to swap contents again: \n";
    swapp(&wallet1, &wallet2);
    std::cout << "wallet1 = " << wallet1 << " $" << std::endl;
    std::cout << "wallet2 = " << wallet2 << " $" << std::endl;

    std::cout << "using value to swap contents: \n";
    swapv(wallet1, wallet2);
    std::cout << "wallet1 = " << wallet1 << " $" << std::endl;
    std::cout << "wallet2 = " << wallet2 << " $" << std::endl;
    return 0;
}

//  using reference
void swapr(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// using pointer
void swapp(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// using value
void swapv(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}