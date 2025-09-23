// firstref.cpp -- defining and using a reference

#include <iostream>

int main()
{
    int rats = 101;
    int& rodents = rats; // rodents is a reference

    std::cout << "rats = " << rats << ", rodents = " << rodents << std::endl;
    rodents++;
    std::cout << "rats = " << rats << ", rodents = " << rodents << std::endl;

    // some implementations require type casting the following address to type unsinged

    std::cout << "rats address = " << &rats << std::endl;
    std::cout << "rodents address = " << &rodents << std::endl;

    return 0;
}