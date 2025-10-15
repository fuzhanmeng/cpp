// twofile1.cpp -- variables with external and internal linkage

#include <iostream>
int tom = 3;            // external variable definition
int dick = 30;          // external variable definition
static int harry = 300; // static, internal linkage

// function prototype
void remote_access();

int main()
{
    std::cout << "main reports the following addresses:\n";
    std::cout << "tom = " << tom << ", &tom = " << &tom << std::endl;
    std::cout << "dick = " << dick << ", &dick = " << &dick << std::endl;
    std::cout << "harry = " << harry << ", &harry = " << &harry << std::endl;

    remote_access();

    return 0;
}