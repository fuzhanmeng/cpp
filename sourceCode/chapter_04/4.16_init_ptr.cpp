// init_ptr -- initialize a pointer

#include <iostream>

int main ()
{
    int higgens = 5;
    int* p_higgens;
    p_higgens = &higgens;

    std::cout << "value of higgens is : " << higgens << std::endl;
    std::cout << "address of higgens is : " << &higgens << std::endl;
    std::cout << "value of p_higgens is " << p_higgens << std::endl;
    std::cout << "address of p_higgens is : " << &p_higgens << std::endl;
    std::cout << "value of *p_higgens is :" << *p_higgens << std::endl;

    return 0;
}