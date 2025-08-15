// address.cpp -- using the & operator to find addresses

#include <iostream>

int main()
{
    int donuts = 6;
    double cups = 4.5;

    std::cout << "donuts value = " << donuts;

    std::cout << " and donuts address = " << &donuts << std::endl;
    // NOTE: you may need to use unsigned (&donuts)
    // and unsigned (&cups)
    std::cout << "cups value = " << cups;
    std::cout << " and cups address = " << &cups << std::endl;
    // cin.get();
    return 0;
}