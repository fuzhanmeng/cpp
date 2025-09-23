// secref.cpp -- defining and using a reference
#include <iostream>
#include <ostream>

int main()
{
    int rats = 101;
    int& rodents = rats;

    std::cout << "rats = " << rats << ", rodents = " << rodents << std::endl;
    std::cout << "rats address = " << &rats << std::endl;
    std::cout << "rodents address = " << &rodents << std::endl;

    int bunnies = 50;
    rodents = bunnies;  // can we change the reference?

    std::cout << "bunnies = " << bunnies << std::endl;
    std::cout << "rats = " << rats << std::endl;
    std::cout << "rodents = " << rodents << std::endl;

    std::cout << "bunnnies address = " << &bunnies << std::endl;
    std::cout << "rodents address = " << &rodents << std::endl;
    std::cout << "rats address = " << &rats << std::endl;

    return 0;
}