// twofile2.cpp -- variables with internal and external linkage

#include <iostream>
extern int tom;
static int dick = 10;
int harry = 200;

void remote_access()
{
    std::cout << "remote_access report the following addresses:\n";
    std::cout << "tom = " << tom << ", &tom = " << &tom << std::endl;
    std::cout << "dick = " << dick << ", &dick = " << &dick << std::endl;
    std::cout << "harry = " << harry << ", &harry = " << &harry << std::endl;
}